#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>

#define PORT 8080
#define SIZE 1024

int main(){
    int clientSocket , serverSocket;
    struct sockaddr_in serverAddress , clientAddress;
    socklen_t clientLength = sizeof(clientAddress);
    char buffer[SIZE];
    char filename[SIZE];
    FILE *fp;

    serverSocket = socket(AF_INET,SOCK_STREAM,0);
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    if(bind(serverSocket , (struct sockaddr*)&serverAddress,sizeof(serverAddress))<0){
        perror("bind failed.");
        exit(1);
    }
    if(listen(serverSocket , 5)<0){
        perror("listen failed.");
        exit(1);
    }

    clientSocket = accept(serverSocket , (struct sockaddr*)&clientAddress,&clientLength);
    int readBytes = read(clientSocket , filename , sizeof(filename));
    filename[readBytes] = '\0';
    printf("Requested file : %s\n",filename);
    fp = fopen(filename,"r");
    if(fp == NULL){
        printf("[EXIT] : file not found error .\n");
        strcpy(buffer,"[EXIT] : File not found.\n");
        send(clientSocket , buffer , strlen(buffer)+1,0);
    }else{
        int readBytes;
        while((readBytes = fread(buffer,1,sizeof(buffer),fp))>0){
            send(clientSocket,buffer,readBytes,0);
        }
        printf("=========FILE READ COMPLETE=====\n");
        fclose(fp);
    }
    close(clientSocket);
    close(serverSocket);
    return 0;
}