#include<iostream>
#include<arpa/inet.h>
#include<unistd.h>
#include<cstring>
#define P 8000
using namespace std;

int main(void){
    int serverSocket = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in sa;
    sa.sin_addr.s_addr = inet_addr("127.0.0.1");
    sa.sin_family = AF_INET;
    sa.sin_port = htons(P);

    bind(serverSocket, (struct sockaddr*)&sa, sizeof(sa));
    cout<<"UDP server listening..."<<endl;
    while(1){
        struct sockaddr_in ca; socklen_t cas = sizeof(ca);
        char buffer[1024]; bzero(buffer, sizeof(buffer));
        recvfrom(serverSocket, buffer, sizeof(buffer),0, (struct sockaddr*)&ca, &cas);
        system(buffer);
        cout<<"Command executed: "<<buffer<<endl;
        string msg = "CMD executed succesfully!"<<endl;
        sendto(serverSocket, msg.c_str(), sizeof(msg.c_str()), 0, (struct sockaddr*)&ca, &cas);
    }
    close(serverSocket);

    return 0;
}