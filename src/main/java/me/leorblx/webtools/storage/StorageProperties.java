package me.leorblx.webtools.storage;

import org.springframework.boot.context.properties.ConfigurationProperties;

@ConfigurationProperties("storage")
public class StorageProperties
{
    /**
     * Folder location for storing files
     */
    private String location = "logs-tmp-upload";

    public String getLocation()
    {
        return location;
    }

    public void setLocation(String location)
    {
        this.location = location;
    }
}