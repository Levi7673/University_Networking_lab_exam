#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<time.h>

#define PORT 8080
#define SIZE 1024
#define ACK_PROB 70
int main(){
    int clientSocket;
    int serverSocket;
    struct sockaddr_in serverAddress;
    struct sockaddr_in clientAddress;
    socklen_t clientLength =  sizeof(clientAddress);

    char receviedBuffer[SIZE];
    char buffer[SIZE];
    int receviedPacket;
    int readBytes;

    // socket creation
    serverSocket = socket(AF_INET,SOCK_STREAM,0);
    // configure serveraddress
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    //bind
    if(bind(
        serverSocket,
        (struct sockaddr*)&serverAddress,
        sizeof(serverAddress)
    )<0){
        perror("bind failed");
        exit(1);
    }
      //liesten
    if(liesten(
        serverSocket,
        (struct sockaddr*)&serverAddress,
        sizeof(serverAddress)
    )<0){
        perror("liesten failed");
        exit(1);
    }

    clientSocket = accept(
        clientSocket,
        (struct sockaddr*)&clientAddress,
        &clientLength
    );
    while(1){
        memset(receivedBuffer,0,SIZE);
        readBytes = read(
            clientSocket,
            receivedBuffer,
            sizeof(receivedBuffer)
        );

        if(readBytes <= 0){
            printf("[EXIT] : transmission complete.\n");
            break;
        }

        receivedPacket = atoi(receivedBuffer);
        printf("[RECEIVED] : received packet %d\n",receivedPacket);
        if(rand()%100 < ACK_PROB){
            printf("[ACK] : ack send for the packet %d\n",receivedPacket);
            sprintf(buffer,"%d",receivedPacket);
            send(
                clientSocket,
                buffer,
                strlen(buffer)+1,
                0
            );
        }else{
            printf("[ACK] : ack not sent for the packet %d\n",receivedPacket);
        }
    }
    close(serverSocket);
    close(clientSocket);
    return 0;
}