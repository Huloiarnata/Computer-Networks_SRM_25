#include<iostream>
#include<cstring>
#include<fstream>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/stat.h>

#define PORT 8000

using namespace std;

int main(void){
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serverA;
    serverA.sin_port = htons(PORT);
    serverA.sin_family = AF_INET;
    serverA.sin_addr.s_addr = inet_addr("127.0.0.1");
    bind(serverSocket, (struct sockaddr*)&serverA,sizeof(serverA));
    listen(serverSocket,1);
    cout<<"FTP server listening..."<<endl;
    struct sockaddr_in clientA; socklen_t clientASize = sizeof(clientA);
    int clientSocket = accept(serverSocket,(struct sockaddr*)&clientA, &clientASize);
    while(1){
        char buffer[1024], file[1024]; 
        bzero(buffer,sizeof(buffer));
        bzero(file,sizeof(file));

        recv(clientSocket, buffer, sizeof(buffer),0);

        FILE* fileptr = fopen(buffer, "r");

        struct stat statVariable;
        
        stat(buffer, &statVariable);
        int size = statVariable.st_size;

        fread(file, sizeof(file), 1, fileptr);
        send(clientSocket, file, sizeof(file),0);
    }

    return 0;
}