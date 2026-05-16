#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>

#define PORT 8080
#define SIZE 1024
int main(){
    int clientSocket,serverSocket;
    struct sockaddr_in serverAddress , clientSocket;
    socklen_t clientLength = sizeof(clientAddress);
      
    //socket creation 
    serverSocket = socket(AF_INET , SOCK_STREAM , 0 );
    if(serverSocket < 0){
        perror("socket creation failed.\n");
        exit(1);
    }

    //configure the server
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    
    // S-B-L-A
    //bind the socket with port
    if(bind(serverSocket,
        (struct sockaddr*)&serverAddress,
        sizeof(serverAddress))<0){
            perror("bind failed.\n");
            exit(1);
        }
    if(listen(serverSocket,5)<0){
        perror("listen failed.\n");
        exit(1);
    }
    printf("Waiting for incoming connection.\n");

    //accept incoming connection
    clientSocket = accept(serverSocket,
                    (struct sockaddr*)&clientAddress,
                    &clientLength);
    printf("Client connected.");

    recv(clientSocket,
        filename,
        sizeof(filename),
        0);
    printf("client requested file : %s",filename);
    filepointer = fopen(filename,"r");

    if (filepointer == NULL){
        strcpy(buffer, 
            "File not found!\n");
        
        send(clientSocket,
            buffer,
            strlen(buffer),
            0)
    }else {
        while(readBytes=)
        close(filepointer)
    }
    return 0;
}