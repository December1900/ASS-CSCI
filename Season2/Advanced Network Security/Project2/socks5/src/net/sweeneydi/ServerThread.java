package net.sweeneydi;

import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.util.Arrays;

public class ServerThread extends Thread {
    private Server mainThread;

    private Socket agentSocket;
    private Socket remoteSocket;

    private InputStream agentIn;
    private OutputStream agentOut;

    private InputStream remoteIn;
    private OutputStream remoteOut;

    private final int BUFFER_SIZE_DEFAULT = 1024;

    private String pw;

    private Cryptogram mCryptogram;


    public ServerThread(Socket agentSocket, Server mainThread, String pw) {
        try {
            this.agentSocket = agentSocket;
            this.remoteSocket = null;

            this.mainThread = mainThread;

            this.agentIn = agentSocket.getInputStream();
            this.agentOut = agentSocket.getOutputStream();
            this.remoteIn = null;
            this.remoteOut = null;
            this.pw = pw;
            this.mCryptogram = new Cryptogram(this.pw);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void over() {
        try {
            agentIn.close();
            agentOut.close();
            agentSocket.close();

            remoteIn.close();
            remoteOut.close();
            remoteSocket.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void run() {
        try {
            agentSocket.setSoTimeout(180000);
            agentSocket.setKeepAlive(true);

            if (!handleSock5HandShake()) return;
            if (!handleSock5Connection()) return;

            startForward();

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private void startForward() {
        try {
            remoteSocket.setSoTimeout(180000);
            remoteSocket.setKeepAlive(true);

            new Decrypt(agentIn, remoteOut, mCryptogram).start();
            new Encrypt(remoteIn, agentOut, mCryptogram).start();

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private boolean handleSock5HandShake() {
        byte[] data = decryptRead(agentIn);
        if (data == null || data[0] != 0x05) return false;

        byte[] response = new byte[2];
        response[0] = 0x05;
        response[1] = 0x00;
        encryptWrite(agentOut, response);
        return true;
    }


    public boolean handleSock5Connection() {
        byte[] data = decryptRead(agentIn);
        SocksReq request = SocksReq.getNewInstance(data);
        if (request == null) return false;

        String remoteAddr = request.getAddress();
        int remotePort = request.getDstPort();
        try {
            remoteSocket = new Socket(remoteAddr, remotePort);
            remoteOut = remoteSocket.getOutputStream();
            remoteIn = remoteSocket.getInputStream();
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }

        byte[] response = SocksResp.responseBytes();
        encryptWrite(agentOut, response);

        return true;
    }

    private byte[] decryptRead(InputStream in) {
        try {
            int len = 0, encryptDataSize = 0;
            byte[] buffer = new byte[BUFFER_SIZE_DEFAULT];
            byte[] encryptData = new byte[BUFFER_SIZE_DEFAULT];

            len = in.read(encryptData);
            encryptDataSize = len;
            if (len == -1) return null;

            while (len == buffer.length) {
                len = in.read(buffer);
                if (encryptData.length < len + encryptDataSize) { //扩容
                    byte[] tempData = encryptData;
                    encryptData = new byte[encryptData.length + BUFFER_SIZE_DEFAULT];
                    if (encryptDataSize >= 0) System.arraycopy(tempData, 0, encryptData, 0, encryptDataSize);
                }
                System.arraycopy(buffer, 0, encryptData, encryptDataSize, len);
                encryptDataSize += len;
            }

            encryptData = Arrays.copyOfRange(encryptData, 0, encryptDataSize);
            return this.mCryptogram.decrypt(encryptData);
        } catch (Exception e) {
            e.printStackTrace();
        }
        return null;
    }


    private void encryptWrite(OutputStream out, byte[] rawData) {
        try {
            byte[] encryptData = this.mCryptogram.encrypt(rawData);
            out.write(encryptData);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
