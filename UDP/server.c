#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

#define PORT 8080
#define SIZE 1024

int main(){
    int serverAddress;
    struct sockaddr_in serverAddress;
    socklen_t serverLength = sizeof(serverAddress);
    char buffer[SIZE];

    printf("=============UDP server===========\n");
    //socket creation 
    serverSocket = socket(AF_INET,SOCK_DGRAM,0);

    //configure the server with ip+port 
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    
    //bind the socket to get server address
    bind(serverSocket,
        (struct sockaddr*)&serverAddress,
        sizeof(serverAddress));

    //realtime loop
    while(1){
        int bytesRecived = recvfrom(serverSocket,
                                buffer,
                                sizeof(buffer),
                                0,
                                (struct sockaddr*)&serverAddress,
                                &serverLength); // recvfrom inu & veenam 
        buffer[bytesRecived] = '\0';
        printf ("Client : %s",buffer);
        if(strcmp(buffer,"exit")==0){
            printf("[Exit] : connection closing.\n");
            break;
        }
        printf("Server : ");
        gets(buffer);
        sendto(serverSocket,
            buffer,
            sizeof(buffer),
            0,
            (struct sockaddr*)&serverAddress,
            serverLength);
        if(strcmp(buffer,"exit")==0){
            printf("[Exit] : connection closing.\n");
            break;
        }
    }
    close(serverSocket);
    return 0;
}