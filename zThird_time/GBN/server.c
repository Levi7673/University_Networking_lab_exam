#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>

#define PORT 8080 
#define SIZE 1024 
#define ACK_PROB 70

int main(){
    int clientSocket;
    int serverSocket;
    struct sockaddr_in serverAddress;
    struct sockaddr_in clientAddress;
    char receviedBuffer[SIZE];
    char buffer[SIZE];
    socklen_t clientLength = sizeof(clientAddress);
    
    serverSocket = socket(AF_INET,SOCK_STREAM,0);
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    //set random seed
    srand(time(0));

    if(bind(serverSocket , (struct sockaddr*)&serverAddress,sizeof(serverAddress))<0){
        perror("bind failed");
        exit(1);
    }
    if(listen(serverSocket,5)<0){
        perror("listen failed");
        exit(1);
    }

    clientSocket = accept(serverSocket , (struct sockaddr*)&clientAddress,&clientLength);
    if(clientSocket<0){
        perror("accpet failed");
        exit(1);
}
while(1){
    memset(receviedBuffer,0,SIZE);
        int readBytes = read(clientSocket , receviedBuffer , sizeof(receviedBuffer));
        if(readBytes <= 0){
            printf("[EXIT] : transmission completed\n");
            break;
        }
        int receivedpacket = atoi(receviedBuffer); 
        if(rand()%100 < ACK_PROB){
            printf("[ACK] : ack send for packet %d\n",receivedpacket);
            sprintf(buffer,"%d",receivedpacket);
            send(clientSocket , buffer , strlen(buffer)+1,0 );
        }else{
            printf("[ACK] : ack lost for packet %d\n",receivedpacket);
        }

}
    close(clientSocket);
    close(serverSocket);
    return 0;
}