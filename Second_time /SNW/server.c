#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<time.h>
#include<stdlib.h>

#define PORT 8080
#define SIZE 1024
#define ACK_PROB 70

int main(){
    int clientSocket;
    int serverSocket;
    struct sockaddr_in serverAddress;
    struct sockaddr_in clientAddress;
    socklen_t clientLength = sizeof(clientAddress);
    char buffer[SIZE];

    //socket creation 
    serverSocket = socket(AF_INET,SOCK_STREAM,0);
    //serveraddress configuration
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    //set random seed 
    srand(time(0));
    //bind the server
    if(bind(
        serverSocket,
        (struct sockaddr*)&serverAddress,
        sizeof(serverAddress)
    )<0){
        perror("bind failed");
        exit(1);
    }
    //listen for incomming connection
    if(listen(
        serverSocket,5
    )<0){
        perror("listen failed");
        exit(1);
    }
    //accept the incomming connection
    clientSocket = accept(
        serverSocket,
        (struct sockaddr*)&clientAddress,
        &clientLength
    );
    //while loop
    while(1){
        int readByte = read(
            clientSocket,
            buffer,
            sizeof(buffer)
        );
        if(readByte<=0)
            break;
        buffer[readByte] = '\0';
        if(strcmp(buffer,"exit")==0){
            printf("[EXIT] : connection closing.\n");
            break;
        }
        printf("[RECEIVED] : packet received %s.\n",buffer);
        if(rand()%100 < ACK_PROB){
            printf("[ACK] : ack sent.\n");
            send(
                clientSocket,
                "ACK",
                strlen("ACK"),
                0
            );
        }else{
            printf("[ACK] : ack lost.\n");
        }
    }
    close(clientSocket);
    close(serverSocket);
    return 0;
}