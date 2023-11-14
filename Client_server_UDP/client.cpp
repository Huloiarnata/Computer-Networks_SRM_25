#include<iostream>
#include<unistd.h>
#include<arpa/inet.h>
#include<cstring>
#define PORT 8000
using namespace std;

int main(void){

    //create socket.
    int clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if(clientSocket<0){
        cerr<<"Error creating socket.\n";
    }

    //creating structure for table.
    struct sockaddr_in serverAddress;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

    //making a sendto call.
    const char* message = "Hello Server!";

    if(sendto(clientSocket, message, sizeof(message), 0, (struct sockaddr*)&serverAddress, sizeof(serverAddress))<0){
        cerr<<"Error Sending message\n";
    }else{
        cerr<<"Message succesfully sent: "<<message<<endl;
    }

}