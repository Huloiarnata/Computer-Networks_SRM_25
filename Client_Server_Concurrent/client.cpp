#include<iostream>
#include<arpa/inet.h>
#include<unistd.h>
#include<cstring>
#include<ctime>
#define PORT 8000

using namespace std;

int main(void){

    //creating client socket.
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    //defining server address structure.
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddr.sin_port = htons(PORT);

    //connecting to port.
    connect(clientSocket,(struct sockaddr*)&serverAddr, sizeof(serverAddr));

    char buffer[1024];
    bzero(buffer, sizeof(buffer));
    recv(clientSocket, buffer, sizeof(buffer), 0);
    cout<<"Date Time recieved: "<<buffer<<endl;
    close(clientSocket);
    return 0;
}