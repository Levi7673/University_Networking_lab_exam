#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<string.h>

#define PORT 8080
#define SIZE 1024

int main(){
    int clientSocket;
    char buffer[SIZE];
    struct sockaddr_in serverAddress;
    socklen_t serverLength = sizeof(serverAddress);

    //socket creation
    clientSocket = socket(AF_INET , SOCK_DGRAM , 0);

    //socket configuration
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

    while(1){
        printf("Client : ");
        fgets(buffer,sizeof(buffer),stdin);
        sendto(clientSocket,
            buffer,
            strlen(buffer),
            0,
            (struct sockaddr*)&serverAddress,
            serverLength);
        
        if(strncmp(buffer,"exit",4)==0){
            printf("[EXIT] : connection closing.\n");
            break;
        }
        int readBytes = recvfrom(clientSocket,
                            buffer,
                            sizeof(buffer),
                            0,
                            (struct sockaddr*)&serverAddress,
                            &serverLength); //recvfrom innu & veenam
        buffer[readBytes] = '\0';
        printf("Server : %s",buffer);
        if(strncmp(buffer,"exit",4)==0){
            printf("[EXIT] : connection closing.\n");
            break;
        }
    }
    close(clientSocket);
    return 0;
}