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
public class DecrypterController {
    private final StorageService storageService;
    private final ServerConfiguration serverConfiguration;

    @Autowired
    public DecrypterController(StorageService storageService, ServerConfiguration serverConfiguration) {
        this.storageService = storageService;
        this.serverConfiguration = serverConfiguration;
    }

    @GetMapping("/file-decrypter")
    public String viewUploadForm(Model model) throws IOException {
        return "uploadForm";
    }

    @PostMapping("/decrypt-upload")
    public String handleFileUpload(Model model, @RequestParam(name = "file", required = false) MultipartFile file,
                                   RedirectAttributes redirectAttributes, HttpServletResponse response) throws IOException {
        String level = "info";

        if (file.isEmpty()) {
            level = "warning";
            redirectAttributes.addFlashAttribute("message", "No file was uploaded.");
        } else {
            if (!file.getOriginalFilename().equalsIgnoreCase("NFSWO_COMMUNICATION_LOG.txt") && !file.getOriginalFilename().equalsIgnoreCase("SystemSettings.dat")) {
                redirectAttributes.addFlashAttribute("message", "Not an acceptable file.");
            } else {
                storageService.store(file);

                String output = serverConfiguration.nativeBridge().decryptWorldFile(
                        storageService.load(file.getOriginalFilename()).toString()
                );

                if (output.startsWith("First special character in wrong position:")
                        || output.equalsIgnoreCase("First special character not found.")
                        || output.equalsIgnoreCase("Decryption failed. Could not open file.")) {
                    level = "danger";
                    redirectAttributes.addFlashAttribute("message", output);
                } else {
                    String token = DownloadManager.genToken();

                    DownloadManager.add(token, new DownloadManager.DownloadInfo(
                            file.getOriginalFilename(),
                            output,
                            DownloadManager.DownloadInfo.DataType.COMMUNICATION_LOG));

                    level = "success";
                    redirectAttributes.addFlashAttribute("message", "Done!");
                    redirectAttributes.addFlashAttribute("url", String.format("/files/%s", token));
                }
//                if (!output.startsWith())
            }
        }

        redirectAttributes.addFlashAttribute("alertClass", "alert alert-" + level);

        return "redirect:/file-decrypter";
    }

    @ExceptionHandler(StorageFileNotFoundException.class)
    public ResponseEntity handleStorageFileNotFound(StorageFileNotFoundException exc) {
        return ResponseEntity.notFound().build();
    }
}
