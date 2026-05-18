#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#include<stdlib.h>

#define PORT 8080
#define SIZE 1024

int main(){
     int clientSocket , serverSocket;
    struct sockaddr_in serverAddress , clientAddress;
    socklen_t clientLength = sizeof(clientLength);
    char buffer[SIZE];

    serverSocket = socket(AF_INET,SOCK_STREAM,0);
    if(clientSocket < 0){
        perror(" socket creation failed");
        exit(1);
    }

    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    if(bind(serverSocket,(struct sockaddr*)&serverAddress,sizeof(serverAddress))<0){
        perror("bind failed");
        exit(1);
    }
    if(listen(serverSocket,5)<0){
        perror("listen failed");
        exit(1);
    }
    clientSocket = accept(serverSocket , (struct sockaddr*)&clientAddress , &clientLength);
    if(clientSocket < 0){
        perror("accept failed");
        exit(1);
    }
    while(1){
        int readBytes = read(clientSocket,buffer,sizeof(buffer));
        buffer[readBytes] = '\0';
        printf("Client : %s",buffer);
        if(strncmp(buffer,"exit",4)==0){
            printf("[EXIT] : connection closing.\n");
            break;
        }
        printf("Server :");
        fgets(buffer,sizeof(buffer),stdin);
        send(clientSocket,buffer,strlen(buffer),0);
        if(strncmp(buffer,"exit",4)==0){
            printf("[EXIT] : connection closing.\n");
            break;
        }
    }
    close(clientSocket);
    close(serverSocket);
    
}