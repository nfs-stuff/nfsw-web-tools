package me.leorblx.webtools;

import me.leorblx.webtools.storage.StorageProperties;
import me.leorblx.webtools.storage.StorageService;
import org.slf4j.LoggerFactory;
import org.springframework.boot.CommandLineRunner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.boot.autoconfigure.security.SecurityAutoConfiguration;
import org.springframework.boot.context.properties.EnableConfigurationProperties;
import org.springframework.context.annotation.Bean;

import java.util.Arrays;

@SpringBootApplication(exclude = {SecurityAutoConfiguration.class})
@EnableConfigurationProperties(StorageProperties.class)
public class Application {

    public static void main(String[] args) {
        NativeBridge nativeBridge = new NativeBridge(); // static trigger
        LoggerFactory.getLogger(Application.class).info("Native test: " + Arrays.toString(Arrays.copyOf(nativeBridge.getAllCarNames(), 5)));
        SpringApplication.run(Application.class);
    }

    @Bean
    CommandLineRunner init(StorageService storageService)
    {
        return (args) -> {
            storageService.deleteAll();
            storageService.init();
        };
    }
}
