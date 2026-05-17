#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<unistd.h>

#define PORT 8080
#define SIZE 1024

int main(){
    int serverSocket;
    char buffer[SIZE];
    struct sockaddr_in serverAddress;
    socklen_t serverLength = sizeof(serverAddress);

    //socket creation
    serverSocket = socket(AF_INET , SOCK_DGRAM , 0);

    //socket configuration
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    if(bind(serverSocket,
        (struct sockaddr*)&serverAddress,
        sizeof(serverAddress))<0){
        perror("bind failed.");
        exit(1);
    }
    //real time chat loop 
    while(1){
        int readBytes = recvfrom(serverSocket,
                            buffer,
                            sizeof(buffer),
                            0,
                            (struct sockaddr*)&serverAddress,
                            &serverLength); //recvfrom innu & veenam
        buffer[readBytes] = '\0';
        printf("Client : %s",buffer);
        if(strncmp(buffer,"exit",4)==0){
            printf("[EXIT] : connection closing.\n");
            break;
    }
    printf("Server : ");
        fgets(buffer,sizeof(buffer),stdin);
        sendto(serverSocket,
            buffer,
            strlen(buffer),
            0,
            (struct sockaddr*)&serverAddress,
            serverLength);
        
        if(strncmp(buffer,"exit",4)==0){
            printf("[EXIT] : connection closing.\n");
            break;
        }
    }
    close(serverSocket);
    return 0;
}