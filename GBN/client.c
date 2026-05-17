#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<sys/time.h>

#define PORT 8080
#define SIZE 1024
#define TIMEOUT_SECOND 3

int main(){

    int clientSocket;

    struct sockaddr_in serverAddress;

    char sendBuffer[SIZE];
    char receivedBuffer[SIZE];

    int windowSize;
    int ackPacket;
    int totalPacket;

    int basePacket = 1;
    int nextPacket = 1;

    printf("Enter the window size : ");
    scanf("%d",&windowSize);

    printf("Enter total packets : ");
    scanf("%d",&totalPacket);

    // socket creation
    clientSocket =
        socket(AF_INET,SOCK_STREAM,0);

    // configure socket
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr =
                inet_addr("127.0.0.1");

    // timeout configuration
    struct timeval receivedTimeout;

    receivedTimeout.tv_sec = TIMEOUT_SECOND;
    receivedTimeout.tv_usec = 0;

    // set socket option
    setsockopt(clientSocket,
            SOL_SOCKET,
            SO_RCVTIMEO,
            &receivedTimeout,
            sizeof(receivedTimeout));

    // connect to receiver
    if(connect(clientSocket,
            (struct sockaddr*)&serverAddress,
            sizeof(serverAddress)) < 0){

        perror("connection failed");
        exit(1);
    }

    printf("\n===========GO BACK N SENDER===========\n");
    printf("[connected] : connected to receiver.\n");

    while(basePacket <= totalPacket){

        // send packets inside window
        while(nextPacket < windowSize + basePacket &&
              nextPacket <= totalPacket){

            sprintf(sendBuffer,
                    "%d",
                    nextPacket);

            send(clientSocket,
                sendBuffer,
                strlen(sendBuffer)+1,
                0);

            printf("[SEND] : packet %d sent\n",
                    nextPacket);

            nextPacket++;
        }

        memset(receivedBuffer,0,SIZE);

        // receive ACK
        int readBytes =
            read(clientSocket,
                receivedBuffer,
                SIZE);

        // ACK received
        if(readBytes > 0){

            ackPacket =
                atoi(receivedBuffer);

            printf("[ACK] : ACK received for packet %d\n",
                    ackPacket);

            // slide window
            basePacket = ackPacket + 1;
        }

        // timeout
        else{

            printf("[TIMEOUT] : ACK not received\n");

            printf("[RETRANSMIT] : retransmitting from packet %d\n",
                    basePacket);

            nextPacket = basePacket;
        }
    }

    printf("[SUCCESS] : all packets transmitted.\n");

    close(clientSocket);

    return 0;
}