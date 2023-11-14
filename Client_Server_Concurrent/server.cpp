#include<iostream>
#include<unistd.h>
#include<arpa/inet.h>
#include<cstring>
#include<ctime>
#define PORT 8000
using namespace std;
int main(){

    //creating socket.
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    //create structure for server.
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    //binding to port.
    bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

    //listening to incoming requests.
    listen(serverSocket, 5);
    cout<<"Listening to client requests..."<<endl;

    //accepting and sending out date time of server.
    while(1){
        struct sockaddr_in clientAddr; socklen_t clientAddrSize = sizeof(clientAddr);
        int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrSize);

        time_t currentTime = time(nullptr);
        string dateTime = ctime(&currentTime);
        send(clientSocket, dateTime.c_str(), dateTime.size(), 0);
        cout<<"DateTime sent to client...\n";

    }
    return 0;

}
