#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>

#define PORT 8080
#define SIZE 1024

int main(){
    int clientSocket;
    int serverSocket;
    struct sockaddr_in serverAddress;
    struct sockaddr_in clientAddress;
    FILE *fp;
    char buffer[SIZE];
    char filename[SIZE];
    int readBytes;
    socklen_t clientLength = sizeof(clientAddress);
    //s-b-l-a
    //socket creation 
    serverSocket = socket(AF_INET,SOCK_STREAM,0);

    //server configuration
    serverAddress.sin_family=AF_INET;
    serverAddress.sin_port=htons(PORT);
    serverAddress.sin_addr.s_addr=INADDR_ANY;

    if(bind(serverSocket,
            (struct sockaddr*)&serverAddress,
            sizeof(serverAddress))<0){
        perror("bind failed");
        exit(1);
    }
    if(listen(serverSocket,5)<0){
        perror("listen failed");
        exit(1);
    }

    clientSocket = accept(serverSocket,
                        (struct sockaddr*)&clientAddress,
                        &clientLength);
    int receivedBytes = recv(clientSocket,  
        filename,
        sizeof(filename),
        0);
    filename[receivedBytes] = '\0';
    printf("Requested file : %s\n",filename);
    
    
    fp = fopen (filename,"r");
    if(fp == NULL){
        strcpy(buffer,"File not found.\n");
        send(clientSocket,
            buffer,
            strlen(buffer)+1,
            0);
        printf("[EXIT] : file not found.\n");
    }else{
        while((readBytes = fread(buffer,1,sizeof(buffer),fp))>0){
            send(clientSocket,
                buffer,
                readBytes,
                0);
        }
         printf("\tFILE READ COMPLETE.\t\n");
         fclose(fp);
    }
   
    close(clientSocket);
    close(serverSocket);
}