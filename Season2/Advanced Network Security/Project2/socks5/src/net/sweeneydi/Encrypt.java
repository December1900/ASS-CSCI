package net.sweeneydi;

import java.io.InputStream;
import java.io.OutputStream;
import java.net.SocketException;
import java.util.Arrays;

public class Encrypt extends Thread {


    private InputStream in;
    private OutputStream out;

    private byte[] buffer;

    private boolean isRunning;

    private static final int BUFFER_SIZE_MIN = 1024 * 128;
    private static final int BUFFER_SIZE_MAX = 1024 * 512;
    private static final int BUFFER_SIZE_STEP = 1024 * 128;

    private Cryptogram mCryptogram;

    public Encrypt(InputStream in, OutputStream out, Cryptogram cryptogram) {
        this.buffer = new byte[BUFFER_SIZE_MIN];
        this.in = in;
        this.out = out;
        this.isRunning = true;
        this.mCryptogram = cryptogram;
    }

    public void run() {
        try {
            int len = 0;
            while ((len = in.read(buffer)) != -1 && isRunning) {
                byte[] rawData = Arrays.copyOfRange(buffer, 0, len);
                byte[] encryptData = this.mCryptogram.encrypt(rawData);

                out.write(encryptData);
                System.out.println("send len=" + encryptData.length);
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
