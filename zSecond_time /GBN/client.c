#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<time.h>

#define PORT 8080
#define SIZE 1024
#define TIMEOUT_SECOND 3
int main(){
    //client
    struct sockaddr_in serverAddress;
    int clientSocket;
    char receivedBuffer[SIZE];
    int receivedPacket;
    char buffer[SIZE];
    int readBytes;
    // socket creation
    clientSocket = socket(AF_INET,SOCK_STREAM,0);
    // configure serveraddress
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    // configure timeval
    struct timeval receivedTimeout;
    receivedTimeout.tv_sec = TIMEOUT_SECOND;
    receivedTimeout.tv_usec = 0;
    // set socket option
    setsockopt(
        clientSocket,
        SOL_SOCKET,
        SO_RCVTIMEO,
        &receivedTimeout,
        sizeof(receivedTimeout)
    );
    // establish connection
    if(connect(
        clientSocket,
        (struct sockaddr*)&serverAddress,
        sizeof(serverAddress)
    )<0){
        perror("connection failed");
        exit(1);
    }
    // prompt user to enter the window size and totalpacket
    int windowSize,totalPacket;
    printf("Enter the window size : ");
    scanf("%d",&windowSize);
    printf("Enter the totapackets : ");
    scanf("%d",&totalPacket);

    int basePacket = 1 ;
    int nextPacket = 1;
    while(basePacket <= totalPacket){
        while(nextPacket < windowSize+basePacket && nextPacket <= totalPacket){
            sprintf(buffer,"%d",nextPacket);
            send(
                clientSocket,
                buffer,
                strlen(buffer)+1,
                0
            );
            printf("[SENT] : send packet %d\n",nextPacket);
            nextPacket++;
        }
        memset ( receivedBuffer , 0 , SIZE);
        readBytes = read(
            clientSocket,
            receivedBuffer,
            sizeof(receivedBuffer)
        );
        if(readBytes <= 0){
            printf("[TIMEOUT] : ack not received.\n[RETRANSMIT] : retransmit packets from %d\n",basePacket);
            nextPacket = basePacket;
        }else{
            int ackPacket = atoi(receivedBuffer);
            printf("[ACK] : ack received for the packet %d\n",ackPacket);
            basePacket = ackPacket + 1;
        }
    }
    printf("\tpacket sent successfully!\t\n");
    close(clientSocket);
}
