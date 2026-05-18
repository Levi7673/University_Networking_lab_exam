#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/time.h>

#define PORT 8080 
#define SIZE 1024 
#define TIMEOUT_SECONDS 3

int main(){
    int clientSocket;
    struct sockaddr_in serverAddress;
    char receviedBuffer[SIZE];
    char buffer[SIZE];
    
    clientSocket = socket(AF_INET,SOCK_STREAM,0);
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

    struct timeval timeoutReceived;
    timeoutReceived.tv_sec = TIMEOUT_SECONDS;
    timeoutReceived.tv_usec = 0;

    setsockopt(clientSocket,SOL_SOCKET,SO_RCVTIMEO,&timeoutReceived,sizeof(timeoutReceived));
    if(connect(clientSocket,(struct sockaddr*)&serverAddress,sizeof(serverAddress))<0){
        perror("connection failed");
        exit(1);
    }

    //GBN
    int windowsize , totalpacket ;

    printf("Enter the window size : ");
    scanf("%d",&windowsize);
    printf("Enter totalpackts : ");
    scanf("%d",&totalpacket);

    int basepacket = 1; //first unacked packet
    int nextpacket = 1;
    while(basepacket <= totalpacket){
        while(nextpacket < windowsize + basepacket && nextpacket <= totalpacket){
            sprintf(buffer,"%d",nextpacket);
            send(clientSocket,buffer,strlen(buffer)+1,0);
            printf("[SENT] : sent packet %s\n",buffer);
            nextpacket ++;
        }
        memset(receviedBuffer,0,SIZE);
        int readBytes = read(clientSocket , receviedBuffer , sizeof(receviedBuffer));
        if(readBytes <= 0){
            printf("[TIMEOUT] : ack lost.\n[RETRANSMIT] : retransmitting the packet from %d\n",basepacket);
            nextpacket = basepacket;
        }else{
            int acked = atoi(receviedBuffer);
            printf("[ACK] : ack received for packet %d\n",acked);
            basepacket = acked + 1;
        }
    }
    printf("[EXIT] : transmission completed\n");
    close(clientSocket);
    return 0;
}