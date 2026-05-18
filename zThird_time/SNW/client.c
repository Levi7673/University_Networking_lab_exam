#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/time.h>
#include<unistd.h>

#define PORT 8080
#define SIZE 1024
#define TIMEOUT_SECOND 3

int main(){
    int clientSocket;
    struct sockaddr_in serverAddress;

    clientSocket = socket(AF_INET , SOCK_STREAM,0);
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

    struct timeval timeoutReceived;
    timeoutReceived.tv_sec = TIMEOUT_SECOND;
    timeoutReceived.tv_usec = 0;

    setsockopt(clientSocket , SOL_SOCKET , SO_RCVTIMEO , &timeoutReceived , sizeof(timeoutReceived));
    
    if(connect(clientSocket , (struct sockaddr*)&serverAddress,sizeof(serverAddress))<0){
        perror("connection failed");
        exit(1);
    }
    //SNW
    char packetToSend[SIZE];
    char packetReceived[SIZE];
    while(1){
        printf("Enter packet / 'exit' :");
        scanf("%s",packetToSend);
        if(strcmp(packetToSend,"exit")==0){
            send(clientSocket,packetToSend,strlen(packetToSend),0);
            printf("[EXIT] : conection closing.\n");
            break;
        }
        int acked=0;
        while(!acked){
            send(clientSocket,packetToSend,strlen(packetToSend)+1,0);
            printf("[SENT] : sent packet %s\n",packetToSend);

            int readBytes = read(clientSocket , packetReceived , sizeof(packetReceived));
            if(readBytes <= 0){
                printf("[TIMEOUT] : ack lost.\n[RETRANSMIT] : retransmit the current packet %s",packetToSend);
                continue;
            }
            packetReceived[readBytes]='\0';
            if(strcmp(packetReceived,"ACK") == 0){
                printf("[ACK] : ack received for packet %s.\n",packetToSend);
                acked = 1;
            }
        }
    }

    close(clientSocket);
    return 0;
}