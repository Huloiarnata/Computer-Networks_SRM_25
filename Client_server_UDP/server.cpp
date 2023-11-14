#include<iostream>
#include<unistd.h>
#include<cstring>
#include<arpa/inet.h>
#define PORT 8000

using namespace std;

int main(void){
    

    //Socket Creation.
    int serverSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if(serverSocket==-1){
        cerr<<"Error creating socket."<<endl;
    }

    //creating structure for table.
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddress.sin_port = htons(PORT);

    //binding socket to the port.
    bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

    cout<<"UDP server listening on 8000"<<endl;

    //client address.
    struct sockaddr_in clientAddress; socklen_t clientAddressSize = sizeof(clientAddress);

    char buff[1024];
    bzero(&buff, sizeof(buff));
    //recieving from client.
    if(recvfrom(serverSocket, buff, sizeof(buff), 0, (struct sockaddr*)&clientAddress, &clientAddressSize)<0){
        cerr<<"error getting message"<<endl;
    }else{
        cout<<"Message recieved is: "<<buff<<endl;
    }
    close(serverSocket);
    return 0;
}