package me.leorblx.webtools;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.util.Arrays;

/**
 * The native library bridge.
 */
public class NativeBridge
{
    private final static Logger logger = LoggerFactory.getLogger(NativeBridge.class);

    static {
        logger.info("***********************************************************************************");
        logger.info("*** Native library initialization sequence beginning.  ");
        logger.info("*** java.library.path: " + System.getProperty("java.library.path"));
        logger.info("***");

        // Load the JNI bridge
        logger.info("***");
        logger.info("*** Loading JNI bridge library...");
        try {
            System.loadLibrary("webtools");

            logger.info("**** Loaded library successfully!");
        } catch (Error | Exception e) {
            logger.error("***********************************************************************************");
            logger.error("*** Failed to load JNI bridge library: ", e);
            logger.error("***********************************************************************************");
        }

        logger.info("***");
        logger.info("*** Native library initialization sequence complete.  ");
        logger.info("***********************************************************************************");
    }

    public long calculateCarHash(String carId)
    {
        return nativePhysicsCalc(carId);
    }

    public long getBaseCar(String carId)
    {
        return nativeBaseCarLookup(carId);
    }

    public String decryptWorldFile(String path)
    {
        return nativeDecrypt(path);
    }

    // Not yet implemented
    public String encryptFile(String path)
    {
        return nativeEncrypt(path);
    }

    public String[] getBaseCarNames() {
        return nativeGetBaseCarNames();
    }

    public String[] getAllCarNames() {
        return nativeGetAllCarNames();
    }

    /**
     * Calculates the PhysicsProfileHash for a car.
     */
    private native long nativePhysicsCalc(String carId);

    /**
     * Gets the BaseCarId for a car.
     */
    private native long nativeBaseCarLookup(String carId);

    /**
     * Decrypts an encrypted log or settings file.
     */
    private native String nativeDecrypt(String path);

    /**
     * Encrypts a decrypted log or settings file.
     * Not yet implemented.
     */
    private native String nativeEncrypt(String path);

    private native String[] nativeGetBaseCarNames();

    private native String[] nativeGetAllCarNames();
}
