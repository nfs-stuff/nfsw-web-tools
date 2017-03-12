package me.leorblx.webtools.controllers;

import me.leorblx.webtools.ServerConfiguration;
import me.leorblx.webtools.managers.DownloadManager;
import me.leorblx.webtools.storage.StorageFileNotFoundException;
import me.leorblx.webtools.storage.StorageService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;
import org.springframework.web.servlet.mvc.support.RedirectAttributes;

import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@Controller
public class EncrypterController
{
    private final StorageService storageService;
    private final ServerConfiguration serverConfiguration;

    @Autowired
    public EncrypterController(StorageService storageService, ServerConfiguration serverConfiguration)
    {
        this.storageService = storageService;
        this.serverConfiguration = serverConfiguration;
    }

    @GetMapping("/file-encrypter")
    public String viewUploadForm(Model model) throws IOException
    {
        return "encryptUploadForm";
    }

    @PostMapping("/encrypt-upload")
    public String handleFileUpload(Model model, @RequestParam(name = "file", required = false) MultipartFile file,
                                   RedirectAttributes redirectAttributes, HttpServletResponse response) throws IOException
    {
        if (file.isEmpty()) {
            redirectAttributes.addFlashAttribute("message", "No file was uploaded.");
        } else {
            if (!file.getOriginalFilename().endsWith(".txt")) {
                redirectAttributes.addFlashAttribute("message", "Not an acceptable file.");
            } else {
                storageService.store(file);

                String output = serverConfiguration.nativeBridge().encryptFile(
                        storageService.load(file.getOriginalFilename()).toString()
                );
                
                String token = DownloadManager.genToken();

                DownloadManager.add(token, new DownloadManager.DownloadInfo(
                        file.getOriginalFilename(),
                        output,
                        DownloadManager.DownloadInfo.DataType.COMMUNICATION_LOG));

                redirectAttributes.addFlashAttribute("message", "Done!");
                redirectAttributes.addFlashAttribute("url", String.format("/files/%s", token));
            }
        }

        return "redirect:/file-encrypter";
    }

    @ExceptionHandler(StorageFileNotFoundException.class)
    public ResponseEntity handleStorageFileNotFound(StorageFileNotFoundException exc)
    {
        return ResponseEntity.notFound().build();
    }
}
