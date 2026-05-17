#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>

#define PORT 8080
#define SIZE 1024

int main(){
    int clientSocket;
    struct sockaddr_in serverAddress;
    char buffer[SIZE];
    char filename[SIZE];
    int readBytes;
    //s-c
    //socket creation 
    clientSocket = socket(AF_INET,SOCK_STREAM,0);

    //server configuration
    serverAddress.sin_family=AF_INET;
    serverAddress.sin_port=htons(PORT);
    serverAddress.sin_addr.s_addr=inet_addr("127.0.0.1");
    
    if(connect(clientSocket,
            (struct sockaddr*)&serverAddress,
            sizeof(serverAddress))<0){
        perror("connection failed");
        exit(1);
    }
    printf("Enter file name : ");
    scanf("%s",filename);

    send(clientSocket,
        filename,
        strlen(filename),
        0);
    printf("=========FILE CONTENT=========\n");
    while((readBytes = read (clientSocket , buffer,sizeof(buffer)))>0){
        fwrite(buffer,
            1,
            readBytes,
            stdout);
    }
    printf("\tFILE READ COMPLETE.\t\n");
    close(clientSocket);
    return 0;
}