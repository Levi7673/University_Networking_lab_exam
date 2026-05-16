//header-socket-bind-listen-accept

#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<stdlib.h>

#define PORT 8080
#define SIZE 1024

int main()
{
    int serverSocket , clientSocket;
    struct sockaddr_in serverAddress , clientAddress;
    socklen_t clientLength = sizeof(clientAddress);
    char  buffer[SIZE];

    printf("================TCP Server===================\n");
    printf("TCP server is running...\n");
    // Create socket
    serverSocket = socket(AF_INET , SOCK_STREAM , 0);
    if(serverSocket < 0){
        perror(" ")
    }
    return 0;
}