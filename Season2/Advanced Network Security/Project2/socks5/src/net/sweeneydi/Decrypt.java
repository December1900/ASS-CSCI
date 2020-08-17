package net.sweeneydi;

import java.io.InputStream;
import java.io.OutputStream;
import java.net.SocketException;
import java.util.Arrays;

public class Decrypt extends Thread {
    private InputStream in;
    private OutputStream out;

    private byte[] buffer;

    private static final int BUFFER_SIZE_MIN = 1024 * 128;
    private static final int BUFFER_SIZE_MAX = 1024 * 512;
    private static final int BUFFER_SIZE_STEP = 1024 * 128;

    private boolean isRunning;

    private Cryptogram mCryptogram;

    public Decrypt(InputStream in, OutputStream out, Cryptogram cryptogram) {
        this.in = in;
        this.out = out;
        this.buffer = new byte[BUFFER_SIZE_MIN];
        this.isRunning = true;
        this.mCryptogram = cryptogram;
    }

    public void run() {
        try {
            int len = 0;
            while ((len = in.read(buffer)) != -1 && isRunning) {
                byte[] encryptData = Arrays.copyOfRange(buffer, 0, len);
                System.out.println("get len=" + encryptData.length);
                byte[] decryptData = this.mCryptogram.decrypt(encryptData);

                out.write(decryptData);
                out.flush();

                if (len == buffer.length && len < BUFFER_SIZE_MAX) {
                    buffer = new byte[len + BUFFER_SIZE_STEP];
                } else if (len < (buffer.length - BUFFER_SIZE_STEP) && (buffer.length - BUFFER_SIZE_STEP) >= BUFFER_SIZE_MIN) {
                    buffer = new byte[buffer.length - BUFFER_SIZE_STEP];
                }
            }
        } catch (SocketException e) {
            isRunning = false;
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
