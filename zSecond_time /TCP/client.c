#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>

#define PORT 8080
#define SIZE 1024

int main(){
    struct sockaddr_in serverAddress;
    int clientSocket;
    char buffer[SIZE];
    //socket creation
    clientSocket = socket(AF_INET,SOCK_STREAM,0);

    //server configuration 
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(clientSocket ,
            (struct sockaddr*)&serverAddress,
            sizeof(serverAddress));
    
    //real time chat loop 
    while(1){
        printf("CLient : ");
        fgets (buffer,sizeof(buffer),stdin);
        send(clientSocket,
            buffer,
            strlen(buffer),
            0);
        if (strncmp(buffer,"exit",4)==0){
            printf("[EXIT] : conenction closing.\n");
            break;
        }
        int readByte = read(clientSocket ,
                            buffer,
                            sizeof(buffer));
        buffer[readByte] = '\0';
        printf("Server : %s\n",buffer);
        if(strncmp(buffer,"exit",4)==0){
            printf("[EXIT] : conenction closing.\n");
            break;
        }
    }
    close(clientSocket);
}