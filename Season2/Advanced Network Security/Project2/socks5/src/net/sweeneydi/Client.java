package net.sweeneydi;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

public class Client {

    private int serverPort;
    private int localPort;
    private String serverAddr;
    private ServerSocket localServerSocket;
    private String pw;

    public Client(String serverAddr, int serverPort, int localPort, String pw) throws IOException {
        this.serverAddr = serverAddr;
        this.serverPort = serverPort;
        this.localPort = localPort;
        this.pw = pw;
    }

    public void listen() {
        try {
            this.localServerSocket = new ServerSocket(this.localPort);
            System.out.println("local listening port: " + serverAddr + ":" + serverPort);
            while (true) {
                try {
                    Socket appSocket = localServerSocket.accept();
                    new ClientThread(this.serverAddr, this.serverPort, appSocket, this, this.pw).start();
                } catch (Exception e) {
                    e.printStackTrace();
                }

            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
