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
    return 0;
}