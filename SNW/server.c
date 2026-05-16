#include<string.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define ACK_PROB 70
#define PORT 8080

int main(){
    int clientSocket , serverAddress;
    struct sockaddr_in serverAddress,clientAddress;
    socklen_t clientLength = sizeof(clientAddress);
    
    //socket creation 
    clientSocket = socket(AF_INET,SOCK_STREAM,0);

    //confgure the server 
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    //bind
    if(bind(clientSocket,
        (struct sockaddr*)&serverAddress)<0){
            perror("bind failed");
            exit(1);//exit with failure 
        }

    if(listen(serverSocket,5)<0){
        perror("listen failed");
        exit(1);//exit with filure 
    }

    clientSocket = accept(serverSocket, 
                    (struct sockaddr*)&clientAddress,
                    &clientLength);
    
    

    return 0;
}