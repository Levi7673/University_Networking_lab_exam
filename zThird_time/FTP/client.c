#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>

#define PORT 8080
#define SIZE 1024

int main(){
    int clientSocket;
    struct sockaddr_in serverAddress;
    char buffer[SIZE];
    char filename[SIZE];

    clientSocket = socket(AF_INET,SOCK_STREAM,0);
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(connect(clientSocket , (struct sockaddr*)&serverAddress,sizeof(serverAddress))<0){
        perror("connection failed.");
        exit(1);
    }

    printf("Enter the file name :");
    scanf("%s",filename);
    send(clientSocket,filename,strlen(filename)+1,0);

    printf("=========FILE CONTENT=========\n");
    int readBytes;
    while((readBytes = read(clientSocket , buffer , sizeof(buffer)))>0){
        fwrite(buffer,1,readBytes,stdout);
    }
    printf("=========FILE READ COMPLETE=====\n");
    close(clientSocket);
    return 0;
}