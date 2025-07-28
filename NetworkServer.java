import java.io.*;
import java.net.*;

public class NetworkServer {
    public static void main(String[] args) {
        int port = 1234;  // Port number for server to listen on

        try {
            // Get and display server IP address
            String serverIP = InetAddress.getLocalHost().getHostAddress();
            System.out.println("Server IP Address: " + serverIP);
            System.out.println("Server Port: " + port);
            System.out.println("Clients should connect to: " + serverIP + ":" + port);
            System.out.println("----------------------------------------");
            
            try (ServerSocket serverSocket = new ServerSocket(port)) {
                System.out.println("Server started. Waiting for client connections...");

                while (true) {  // Keep accepting multiple clients
                    Socket clientSocket = serverSocket.accept();
                    String clientIP = clientSocket.getInetAddress().getHostAddress();
                    System.out.println("Client connected from: " + clientIP);

                    BufferedReader in = new BufferedReader(
                        new InputStreamReader(clientSocket.getInputStream()));
                    PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true);

                    String message = in.readLine();
                    System.out.println("Received from client (" + clientIP + "): " + message);

                    out.println("Hello Client from " + clientIP + ", message received!");

                    in.close();
                    out.close();
                    clientSocket.close();
                    System.out.println("Client " + clientIP + " disconnected.");
                    System.out.println("Waiting for next client...");
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
