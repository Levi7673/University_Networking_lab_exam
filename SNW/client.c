#include<stdio.h>
#include<unistd.h>
#include<sys/time.h>
#include<arpa/inet.h>
#include<string.h>

#define PORT 8080
#define SIZE 1024
#define TIMEOUT_SECOND 3

int main(){
    struct timeval receivedTimeout;
    char packetSendTo[SIZE];
    char receviedMessage[SIZE];
    int clientSocket;
    struct sockaddr_in serverAddress;

    srand(time(0));
    clientSocket = socket(AF_INET,SOCK_STREAM,0);
    if(clientSocket < 0){
        perror("Socket failed.");
        exit(1);
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(clientSocket,
        (struct sockaddr*)&serverAddress,
        sizeof(serverAddress));
    
    receivedTimeout.tv_sec = TIMEOUT_SECOND;
    receivedTimeout.tv_usec = 0;
    setsockopt(clientSocket,
            SOL_,
            SO_RCVTIMEO,
            );

    return 0;
}