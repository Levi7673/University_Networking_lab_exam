#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/time.h>
#include<unistd.h>

#define PORT 8080
#define SIZE 1024
#define ACK_PROB 70

int main(){
    socklen_t clientLength = sizeof(clientAddress);
    //S_B_L_A
    //socket creation  
    serverSocket = socket(AF_INET,SOCK_STREAM,0);

    // configure the socket 
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    //set random seed 
    srand(time(0));

    if(bind(serverSocket,
        (struct sockaddr*)&serverAddress,
        sizeof(serverAddress))<0){
        perror("Bind failed.");
        exit(1);
    }
    if(listen(serverSocket,5)<0){
        perror("listen failed.");
        exit(1);
    }

    clientSocket = accept(serverSocket,
                    (struct sockaddr*)&clientAddress,
                    &clientLength);
    while(1){
        int readBytes = read(clientSocket , receivedBuffer , sizeof(receivedBuffer));
        if(readBytes < 0){
            printf("[EXIT] : transmission complete.\n");
        receivedpacket = atoi(receivedBuffer);
        printf("[RECEIVE] : received packet %s",receivedpacket);
        if(rand()%100 < ACK_PROB){
            printf("[ACK] : ack lost for packet %s .\n",receivedpacket);
        }else{
            sprintf(receivedBuffer , "%s" , receivedpacket);
            send(clientSocket,
                receivedBuffer,
                sizeof(receivedBuffer),
                0);
            printf("[ACK] : ack send for the packet %s",receivedBuffer);
        }
    }
    close(clientSocket);
    close(serverSocket);
    return 0;
}