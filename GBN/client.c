#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<time.h>
#include<unistd.h>

#define PORT 8080
#define SIZE 1024
#define TIMEOUT_SECOND 3

int main(){
    int clientSocket;
    struct sockaddr_in serverAddress;
    char sendBuffer[SIZE];
    char receivedBuffer[SIZE];

    int windowsize;
    int totalpacket;
    int basepacket = 1;
    int nextpacket = 1;

    printf("Enter the window size : ");
    scanf("%d",&windowsize);

    printf("Enter total packets : ");
    scanf("%d",&totalpacket);

    //socket creation  
    clientSocket = socket(AF_INET,SOCK_STREAM,0);

    // configure the socket 
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

    //configure the timeval 
    struct timeval receivedTimeout;
    receivedTimeout.tv_sec = TIMEOUT_SECOND;
    receivedTimeout.tv_usec = 0;

    //set socket option 
    setsockopt(clientSocket,
            SOL_SOCKET,
            SO_RCVTIMEO,
            &receivedTimeout,
            sizeof(receivedTimeout));
    
    if(connect(clientSocket , 
            (struct sockaddr*)&serverAddress,
            sizeof(serverAddress))<0){
        perror("connection failed.");
        exit(1);
    }

    while(basepacket <= totalpacket){
        while(nextpacket < windowsize + basepacket && nextpacket <= totalpacket){
            sprintf(sendBuffer , "%d" , nextpacket)
            send(clientSocket,
                sendBuffer,
                strlen(sendBuffer),
                0);
            int readBytes=read(clientSocket,
                            receivedBuffer,
                            sizeof(receivedBuffer));
            int 
            printf()
            nextpacket ++;
        }
        if(readBytes > 0){

        }else{
            printf("[RETRANSMIT] : retransmitting the packet.\n")
            nextpacket = basepacket
        }
    }
    close(clientSocket);
    return 0;
}