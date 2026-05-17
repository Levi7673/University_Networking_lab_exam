#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>

#define PORT 8080
#define SIZE 1024

int main(){
    struct sockaddr_in serverAddress , clientAddress;
    int clientSocket,serverSocket;
    char buffer[SIZE];
    socklen_t clientLength = sizeof(clientAddress);
    //socket creation
    serverSocket = socket(AF_INET,SOCK_STREAM,0);

    //server configuration 
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

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
    //realtime while loop 
    while(1){
        int readByte = read(clientSocket,
                            buffer,
                            sizeof(buffer));
        buffer[readByte] = '\0';
        printf("Cient : %s\n",buffer);
        if(strncmp(buffer,"exit",4)==0){
            printf("[EXIT] : conenction closing.\n");
            break;
        }
        printf("Server : ");
        fgets(buffer,sizeof(buffer),stdin);
        send(clientSocket,
            buffer,
            strlen(buffer),
            0);
        if(strncmp(buffer,"exit",4)==0){
            printf("[EXIT] : conenction closing.\n");
            break;
        }
    }   
    return 0;
}