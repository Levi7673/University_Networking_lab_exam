#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<time.h>
#include<unistd.h>

#define PORT 8080
#define SIZE 1024
#define ACK_PROB 70

int main(){
    int clientSocket;
    int serverSocket;
    struct sockaddr_in serverAddress;
    struct sockaddr_in clientAddress;
    socklen_t clientLength = sizeof(clientAddress);

    serverSocket = socket(AF_INET , SOCK_STREAM,0);
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    srand(time(0));
    if(bind(serverSocket , (struct sockaddr*)&serverAddress,sizeof(serverAddress))<0){
        perror("bind failed");
        exit(1);
    }
    if(listen(serverSocket , 5)<0){
        perror("listen failed");
        exit(1);
    }
    clientSocket = accept(serverSocket ,(struct sockaddr*)&clientAddress , &clientLength);
    //SNW
    char receivedBuffer[SIZE];
    while(1){
        int readBytes = read(clientSocket , receivedBuffer , sizeof(receivedBuffer));
        if (readBytes <= 0){
            break;
        }
        receivedBuffer[readBytes] = '\0';
        if(rand()%100 < ACK_PROB){
            printf("[ACK] : ack sent for packet %s.\n",receivedBuffer);
            send(clientSocket , "ACK" , strlen("ACK")+1,0);
        }else{
            printf("[ACK] : ack lost for packet %s.\n",receivedBuffer);
        }
    }

    close(clientSocket);
    close(serverSocket);
    return 0;
}