#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#include<stdlib.h>

#define PORT 8080
#define SIZE 1024

int main(){
    int clientSocket;
    struct sockaddr_in serverAddress;
    char buffer[SIZE];

    clientSocket = socket(AF_INET,SOCK_STREAM,0);
    if(clientSocket < 0){
        perror("socket creation failed");
        exit(1);
    }
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    if(connect(clientSocket,(struct sockaddr*)&serverAddress,sizeof(serverAddress))<0){
        perror("connection failed");
        exit(1);
    }
    while(1){
        printf("client :");
        fgets(buffer,sizeof(buffer),stdin);
        send(clientSocket,buffer,strlen(buffer),0);
        if(strncmp(buffer,"exit",4)==0){
            printf("[EXIT] : connection closing.\n");
            break;
        }
        int readBytes = read(clientSocket,buffer,sizeof(buffer));
        buffer[readBytes] = '\0';
        printf("Server : %s",buffer);
        if(strncmp(buffer,"exit",4)==0){
            printf("[EXIT] : connection closing.\n");
            break;
        }
    }
    close(clientSocket);
    return 0;
}
