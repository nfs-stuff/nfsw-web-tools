package me.leorblx.webtools.controllers;

import me.leorblx.webtools.managers.DownloadManager;
import me.leorblx.webtools.storage.StorageService;
import org.apache.tomcat.util.http.fileupload.IOUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;

import javax.servlet.http.HttpServletResponse;
import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.io.InputStream;

@Controller
public class FilesController {
    private final StorageService storageService;

    @Autowired
    public FilesController(StorageService storageService) {
        this.storageService = storageService;
    }

    @GetMapping("/files/{token:[A-Za-z0-9]+}")
    public void download(
            @PathVariable String token,
            HttpServletResponse response
    ) throws IOException {
        if (!DownloadManager.pendingDownloads.containsKey(token)) {
            throw new IllegalArgumentException("Invalid token!");
        }

        InputStream inputStream = new ByteArrayInputStream(
                DownloadManager.pendingDownloads.get(token).getContent().getBytes()
        );

        storageService.load(DownloadManager.pendingDownloads.remove(token).getFileName()).toFile().delete();

        response.addHeader("Content-disposition", "attachment;filename=" + token + "-result.txt");
        response.setContentType("txt/plain");

        IOUtils.copy(inputStream, response.getOutputStream());

        response.flushBuffer();
    }
}
