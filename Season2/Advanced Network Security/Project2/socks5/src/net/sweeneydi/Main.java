package net.sweeneydi;

import java.io.IOException;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) throws Exception {
        if (args.length == 0) {
            throw new Exception("Client and Server address ports are not specified");
        }
        String clientStr = "";
        String serverStr = "";
        for (int i = 0; i < args.length; i++) {
            try {
                if (args[i].equals("-c")) {
                    clientStr = args[i + 1];
                }
                if (args[i].equals("-s")) {
                    serverStr = args[i + 1];
                }
            } catch (Exception e) {
                if (e instanceof IndexOutOfBoundsException) {
                    System.out.println("parameter parsing error");
                }
                throw e;
            }
        }


        Scanner sc = new Scanner(System.in);
        System.out.println("enter no more than 8 char password:");
        String pw = sc.nextLine();
        if (pw.length() >= 8) {
            pw = pw.substring(0, 8);
        }
        try {
            String[] client = clientStr.split(":");
            String clientPort = client[1];
            String[] server = serverStr.split(":");
            String serverAddr = server[0];
            String serverPort = server[1];

            new ServerStartThread(Integer.parseInt(serverPort), pw).start();
            new ClientStartThread(serverAddr, Integer.parseInt(serverPort), Integer.parseInt(clientPort), pw).start();

        } catch (Exception e) {
            if (e instanceof IndexOutOfBoundsException) {
                System.out.println("parameter parsing error");
            }
            throw e;
        }
    }
}

class ServerStartThread extends Thread {
    private int port;
    private String pw;

    public ServerStartThread(int port, String pw) {
        this.pw = pw;
        this.port = port;
    }

    public void run() {
        serverStart(this.port, this.pw);
    }

    private void serverStart(int port, String pw) {
        Server server = new Server(port, pw);
        server.listen();
    }
}

class ClientStartThread extends Thread {
    private String serverAddr;
    private int serverPort;
    private int localPort;
    private String pw;

    public ClientStartThread(String serverAddr, int serverPort, int localPort, String pw) {
        this.serverAddr = serverAddr;
        this.serverPort = serverPort;
        this.localPort = localPort;
        this.pw = pw;
    }

    public void run() {
        try {
            localStart(this.serverAddr, this.serverPort, this.localPort, this.pw);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void localStart(String serverAddr, int serverPort, int localPort, String pw) throws IOException {
        Client client = new Client(serverAddr, serverPort, localPort, pw);
        client.listen();
    }
}
