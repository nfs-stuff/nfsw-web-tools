package me.leorblx.webtools.managers;

import java.math.BigInteger;
import java.security.SecureRandom;
import java.util.HashMap;
import java.util.Map;

public class DownloadManager
{
    private static final SecureRandom random = new SecureRandom();
    public static Map<String, DownloadInfo> pendingDownloads = new HashMap<>();

    public static void add(String token, DownloadInfo downloadInfo)
    {
        pendingDownloads.put(token, downloadInfo);
    }

    public static void complete(String token)
    {
        pendingDownloads.remove(token);
    }

    public static String genToken()
    {
        return new BigInteger(130, random).toString(32);
    }

    public static class DownloadInfo
    {
        private String fileName;
        private String content;
        private DataType dataType;

        public DownloadInfo(String fileName, String content, DataType dataType)
        {
            this.fileName = fileName;
            this.content = content;
            this.dataType = dataType;
        }

        public String getContent()
        {
            return content;
        }

        public DataType getDataType() {
            return dataType;
        }

        public String getFileName()
        {
            return fileName;
        }

        public enum DataType {
            COMMUNICATION_LOG,
            SYSTEM_SETTINGS
        }
    }
}
