package net.sweeneydi;

import java.io.*;
import java.net.Socket;

public class ClientThread extends Thread {

    private InputStream localIn;
    private OutputStream localOut;
    private InputStream hostIn;
    private OutputStream hostOut;
    private Socket hostSocket;
    private Socket localSocket;
    private Client mainThread;
    private Cryptogram mCryptogram;
    private String pw;

    public ClientThread(String hostAddr, int hostPort, Socket localSocket, Client mainThread, String pw) {
        try {
            this.localSocket = localSocket;
            this.hostSocket = new Socket(hostAddr, hostPort);
            this.localIn = localSocket.getInputStream();
            this.localOut = localSocket.getOutputStream();
            this.hostIn = hostSocket.getInputStream();
            this.hostOut = hostSocket.getOutputStream();
            this.mainThread = mainThread;
            this.mCryptogram = new Cryptogram(this.pw);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void run() {
        try {

            hostSocket.setSoTimeout(180000);
            localSocket.setSoTimeout(180000);

            hostSocket.setKeepAlive(true);
            localSocket.setKeepAlive(true);

            new Encrypt(localIn, hostOut, mCryptogram).start();
            new Decrypt(hostIn, localOut, mCryptogram).start();

        } catch (Exception e) {
            e.printStackTrace();
        }
    }


}
