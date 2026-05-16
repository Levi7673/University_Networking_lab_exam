#include<stdio.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#define PORT 8080
#define SIZE 1024

int main()
{
    int clientSocket;
    char buffer[SIZE];
    struct sockaddr_in serverAddress;
    printf("================TCP Client===================\n");
    printf("TCP Client is running...\n");
    // Create socket
    clientSocket = socket(AF_INET , SOCK_STREAM , 0);
    if(clientSocket < 0){
        perror("socket creation failed");
        exit(1);//exit with failure
    }
    //configure server address
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    //connect to server

    printf("connecting to server...\n");
    if(connect(clientSocket,
        (struct sockaddr*)&serverAddress,
        sizeof(serverAddress))<0){
            perror("connection failed");
            exit(1); // exit with failure
        }
    printf("Connected to server.\n");
    // realtime chat simulation
    while(1){
        printf("Client : ");
        fgets(buffer,sizeof(buffer),stdin); // read i/p from user (keyboard)
        send(clientSocket,buffer,strlen(buffer),0); // send message to server
        if(strncmp(buffer,"exit",4)==0){
            printf("[exit] closing connection...\n");
            break;
        }
        int readBytes = read(clientSocket,buffer,sizeof(buffer)); // read message from server
        buffer[readBytes] = '\0';
        printf("Server : %s",buffer);
        if(strncmp(buffer,"exit",4)==0){
            printf("[exit] closing connection...\n");
            break;
        }
    }
    close(clientSocket);
    return 0;
}