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
        perror("socket creation failed");
        exit(1); // exit with failure
    }
    //configure server address
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    //bind the socket to the specified ip and port
    if(bind(serverSocket,
        (struct sockaddr*)&serverAddress,
        sizeof(serverAddress))<0){
            perror("bind failed");
            exit(1); // exit with failure
        }
    //listen for incoming connections
    if(listen(serverSocket,5)<0){
        perror("listen failed");
        exit(1); // exit with failure
    }

    //accept incomming connection
    printf("waiting for incoming connections...\n");
    clientSocket = accept(serverSocket,
                        (struct sockaddr*)&serverAddress,
                        &clientLength);
    //real time chat loop 
    while(1){
        int bytesRecived = read(clientSocket ,
                            buffer ,
                            sizeof(buffer));
        buffer[bytesRecived]='\0';
        printf("client : %s",buffer);
        if(strncmp(buffer,"exit",4)==0){
            printf("[EXIT] : connection closing.\n");
            break;
        }
        printf("Server : ");
        fgets(buffer,sizeof(buffer),stdin);
        send(clientSocket,
            buffer,
            strlen(buffer),
            0);
        if(strncmp(buffer,"exit",4)==0){
            printf("[EXIT] : connection closing.");
            break;
        }
    }
    close(serverSocket);
    close(clientSocket);
    return 0;
}