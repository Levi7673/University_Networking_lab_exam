#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

#define PORT 8080
#define SIZE 1024 

int main(){
    int clientSocket;
    struct sockaddr_in serverAddress;
    socklen_t clientLength = sizeof(cilentAddress);
    char buffe[SIZE];

    printf("============UDP CLIENT=============\n");
    //socket creation
    clientSocket=socket(AF_INET,SOCK_DGRAM,0);

    //configure the server with ip+port 
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

    while(1){
        printf("Client : ");
        gets(buffer);
        sendto(clientSocket,
            buffer,
            sizeof(buffer),
            0,
            (struct sockaddr*)&serverAddress,
            clientLength); //send inu &illa
        if(strcmp(buffer,"exit")==0){
            printf("[Exit] : connection closing.\n");
            break;
        }
        int  bytesRecived = recvfrom(clientSocket,
                                buffer,
                                sizeof(buffer),
                                0,
                                (struct sockaddr*)&serverAddress,
                                &clientLength); //recvfrom inu & ondu
        buffer[bytesRecived] = '\0';
        printf("Server : %s",buffer);
        if(strcmp(bufffer,"exit")==0){
            printf("[Exit] : connection closing.");
            break;
        }
    }
    close(clientSocket);
    return 0;
}