#include<iostream>
#include<arpa/inet.h>
#include<netdb.h>
#include<unistd.h>
#include<cstring>

using namespace std;

int main(){

    //creating client socket.
    int clientSocket = socket(AF_INET, SOCK_STREAM,0);

    //creating a structure.
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;

    int port; cout<<"Enter PORT"; cin>>port;
    serverAddr.sin_port = htons(port);

    string IPAddress; cout<<"Enter IP address: "; cin>>IPAddress;
    serverAddr.sin_addr.s_addr = inet_addr(IPAddress.c_str());

    //connect.
    connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

    if(fork()==0){
        //child process will recv msg from server and print.
        while(1){
            char recv_buff[1024];
            bzero(recv_buff, sizeof(recv_buff));
            recv(clientSocket, recv_buff, sizeof(recv_buff), 0);
            cout<<"Server: "<<recv_buff<<endl;
        }
    }else{
        //parent process will take i/p from the client and send to server.
        while(1){
            char send_buff[1024];
            bzero(send_buff, sizeof(send_buff));
            cout<<"Enter message for server: ";cin.getline(send_buff, sizeof(send_buff));
            send(clientSocket, send_buff, strlen(send_buff), 0);
            cout<<endl<<endl;
        }

    }
    return 0;
}