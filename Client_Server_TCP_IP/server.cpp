//libraries.
#include<iostream>
#include<cstring>
#include<unistd.h>
#include<arpa/inet.h>
#define PORT 8000
using namespace std;

int main(void){

    //creating socket.
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    //server address for table.
    struct sockaddr_in serverAddress;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

    //binding socket to port number.
    bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

    //listening for requests.
    listen(serverSocket,1);

    //creating a clientAdress structure.
    struct sockaddr_in clientAddress;
    socklen_t clientAddressSize = sizeof(clientAddress);
    
    //accepting requests.
    int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddressSize);

    //recieveing messages from client.
    char buff[1024];
    bzero(&buff, sizeof(buff));
    recv(clientSocket, buff, sizeof(buff), 0);
    printf("Message Recieved is: %s\n", buff);

    //closing sockets.
    close(clientSocket);
    close(serverSocket);

    return 0;
}

