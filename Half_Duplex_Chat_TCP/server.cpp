#include<iostream>
#include<cstring>
#include<unistd.h>
#include<arpa/inet.h>
#define PORT 8000

using namespace std;

int main(void){
    //creating server socket.
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    //creating structure for table.
    struct sockaddr_in serverAddr ;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    serverAddr.sin_family = AF_INET; //TCP/IP

    //binding to port.
    bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

    //Listening for connections.
    cout<<"Listening for clients..."<<endl;
    listen(serverSocket, 5);

    //accepting connection
    int clientSocket = accept(serverSocket,nullptr,nullptr);

    //creating processes to handle chatting component.
    if(fork()==0){
        // child process will recv msg and print.
        while(1){
            char buffer[1024];
            bzero(buffer, sizeof(buffer));
            recv(clientSocket, buffer, sizeof(buffer),0);
            cout<<"Client: "<<buffer<<endl;
        }
    }else{
        // parent process will send msg.
        while(1){
            char send_buffer[1024];
            bzero(send_buffer,sizeof(send_buffer));
            cout<<"Enter msg for client: ";
            cin.getline(send_buffer, sizeof(send_buffer));
            send(clientSocket, send_buffer, strlen(send_buffer),0);cout<<endl;
            cout<<endl<<endl;
        }
    }

    return 0;
}
