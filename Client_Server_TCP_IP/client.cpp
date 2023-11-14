#include<iostream>
#include<cstring>
#include<unistd.h>
#include<arpa/inet.h>
#define PORT 8000
using namespace std;
int main(void){

    //creating clientSocket.
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    //server address for table.
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddress.sin_port = htons(PORT);

    //conecting to socket.
    connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
    cout<<"Connected to server...\n";
    const char* msg = "Hello World!";

    //sending msg to server.
    send(clientSocket, msg, strlen(msg), 0);
    close(clientSocket);
    return 0;
}

