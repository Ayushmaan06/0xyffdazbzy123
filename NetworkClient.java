import java.io.*;
import java.net.*;
import java.util.Scanner;

public class NetworkClient {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        // Allow user to input server address
        System.out.print("Enter server IP address (or 'localhost' for local): ");
        String serverAddress = scanner.nextLine();
        
        // Default to localhost if empty
        if (serverAddress.trim().isEmpty()) {
            serverAddress = "localhost";
        }
        
        int port = 1234;
        
        System.out.println("Attempting to connect to " + serverAddress + ":" + port);

        try (Socket socket = new Socket(serverAddress, port)) {
            System.out.println("Connected to server!");
            
            BufferedReader in = new BufferedReader(
                new InputStreamReader(socket.getInputStream()));
            PrintWriter out = new PrintWriter(socket.getOutputStream(), true);

            // Get message from user
            System.out.print("Enter message to send to server: ");
            String message = scanner.nextLine();
            
            if (message.trim().isEmpty()) {
                message = "Hello Server from remote client!";
            }
            
            out.println(message);
            System.out.println("Message sent: " + message);

            String response = in.readLine();
            System.out.println("Response from server: " + response);

            in.close();
            out.close();
        } catch (ConnectException e) {
            System.err.println("Could not connect to server at " + serverAddress + ":" + port);
            System.err.println("Make sure the server is running and reachable.");
        } catch (IOException e) {
            System.err.println("Network error: " + e.getMessage());
            e.printStackTrace();
        } finally {
            scanner.close();
        }
    }
}
