#include<iostream>
#include<sys/stat.h>
#include<cstring>
#include<fstream>
#include<unistd.h>
#include<arpa/inet.h>

#define PORT 8000

using namespace std;

int main(void){
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in sa;
    sa.sin_port=htons(PORT);
    sa.sin_addr.s_addr = inet_addr("127.0.0.1");
    sa.sin_family = AF_INET;

    connect(clientSocket, (struct sockaddr*)&sa, sizeof(sa));
    while(1){
        cout<<"Enter file name: "; string name;cin>>name;
        send(clientSocket, name.c_str(), strlen(name.c_str())+1, 0);
        char file[1024]; bzero(file, sizeof(file));
        recv(clientSocket, file, sizeof(file),0);
        cout<<"File content are: "<<file<<endl;
    }
    return 0;
}