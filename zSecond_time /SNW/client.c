#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/time.h>
#include<stdlib.h>

#define PORT 8080
#define SIZE 1024
#define TIMEOUT_SECOND 3

int main(){
    int clientSocket;
    struct sockaddr_in serverAddress;
    struct timeval timeoutReceived;
    char packetToSend[SIZE];
    char packetReceived[SIZE];

    //socket creation 
    clientSocket = socket(AF_INET,SOCK_STREAM,0);
    //serveraddress configuration
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    //timeval configuration
    timeoutReceived.tv_sec = TIMEOUT_SECOND;
    timeoutReceived.tv_usec = 0;
    //set socket option
    setsockopt(
        clientSocket,
        SOL_SOCKET,
        SO_RCVTIMEO,
        &timeoutReceived,
        sizeof(timeoutReceived)
    );
    //establish connection and connect to the server.
    if(connect(
        clientSocket,
        (struct sockaddr*)&serverAddress,
        sizeof(serverAddress)
    )<0){
        perror("connetion failed");
        exit(1);
    }
    //while loop
    while(1){
        printf("Enter packet number / 'exit': ");
        scanf("%s",packetToSend);

        if(strcmp(packetToSend,"exit")==0){
            send(
                clientSocket,
                packetToSend,
                strlen(packetToSend),
                0
            );
            printf("[EXIT] : connection closing.");
            break;
        }
        
        int ackReceived = 0;
        while(!ackReceived){
            send(
            clientSocket,
            packetToSend,
            strlen(packetToSend),
            0
        );
        int readByte = read(
            clientSocket,
            packetReceived,
            sizeof(packetReceived)
        );
            if(readByte <= 0){
                printf("[TIMEOUT] : ack not received.\n");
                printf("[RETRANSMIT] : retransmit the current packet %s.\n",packetToSend);
                continue;
            }
            packetReceived[readByte] = '\0';
            if (strcmp(packetReceived,"ACK")==0){
                printf("[ACK] : ack received.\n");
                ackReceived =1;
            }
        }
    }
    close(clientSocket);
    return 0;
}