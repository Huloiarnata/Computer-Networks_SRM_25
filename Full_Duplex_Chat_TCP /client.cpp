// fullduplex_client.cpp
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

int main() {
    // Create socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    // Initialize server address
    sockaddr_in serverAddress;
    bzero(&serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;

    // Get the server IP address and port from the console
    std::cout << "Enter server IP address: ";
    std::string ipAddress;
    std::cin >> ipAddress;
    serverAddress.sin_addr.s_addr = inet_addr(ipAddress.c_str());
    std::cout << "Enter server port: ";
    int port;
    std::cin >> port;
    serverAddress.sin_port = htons(port);

    // Request a connection from the server
    connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

    // Fork the process to handle both sending and receiving messages
    if (fork() == 0) {
        // Child process handles sending messages to the server
        while (true) {
            char buffer[BUFFER_SIZE];
            std::cout << "Enter message for the server: ";
            std::cin.getline(buffer, sizeof(buffer));
            write(clientSocket, buffer, strlen(buffer));
        }
    } else {
        // Parent process handles receiving messages from the server
        while (true) {
            char buffer[BUFFER_SIZE];
            ssize_t bytesRead = read(clientSocket, buffer, sizeof(buffer));
            buffer[bytesRead] = '\0';
            std::cout << "Server: " << buffer << std::endl;
        }
    }

    // Close the client socket
    close(clientSocket);

    return 0;
}
