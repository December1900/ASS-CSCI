package net.sweeneydi;

import java.net.ServerSocket;
import java.net.Socket;

public class Server {
    private int port;
    private ServerSocket serverSocket;
    private String pw;

    public Server(int port, String pw) {
        this.port = port;
        this.pw = pw;
    }

    public void listen() {
        try {
            System.out.println("server listening port: " + port);
            serverSocket = new ServerSocket(port);
            while (true) {
                Socket socket = serverSocket.accept();
                new ServerThread(socket, this, this.pw).start();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

}
