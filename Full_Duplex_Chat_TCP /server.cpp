// fullduplex_server.cpp
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

int main() {
    // Create socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    // Initialize server address
    sockaddr_in serverAddress;
    bzero(&serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(12345); // You can use any available port

    // Bind the socket
    bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

    // Listen for incoming connections
    listen(serverSocket, 1);

    std::cout << "Server listening for incoming connection..." << std::endl;

    // Accept connection request from the client
    int clientSocket = accept(serverSocket, nullptr, nullptr);

    // Fork the process to handle both sending and receiving messages
    if (fork() == 0) {
        // Child process handles sending messages to the client
        while (true) {
            char buffer[BUFFER_SIZE];
            std::cout << "Enter message for the client: ";
            std::cin.getline(buffer, sizeof(buffer));
            write(clientSocket, buffer, strlen(buffer));
        }
    } else {
        // Parent process handles receiving messages from the client
        while (true) {
            char buffer[BUFFER_SIZE];
            ssize_t bytesRead = read(clientSocket, buffer, sizeof(buffer));
            buffer[bytesRead] = '\0';
            std::cout << "Client: " << buffer << std::endl;
        }
    }

    // Close the server socket
    close(serverSocket);

    return 0;
}
