#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>

#define PORT 8080
#define SIZE 1024

int main(){

    int clientSocket , serverSocket;
    int readBytes;

    struct sockaddr_in serverAddress ,
                        clientAddress;

    socklen_t clientLength =
                    sizeof(clientAddress);

    char filename[SIZE];
    char buffer[SIZE];

    FILE *filepointer;

    printf("\n===========FTP SERVER===========\n");

    // socket creation
    serverSocket = socket(AF_INET ,
                          SOCK_STREAM ,
                          0);

    if(serverSocket < 0){
        perror("socket creation failed");
        exit(1);
    }

    // configure server
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    // bind socket with port
    if(bind(serverSocket ,
        (struct sockaddr*)&serverAddress ,
        sizeof(serverAddress)) < 0){

        perror("bind failed");
        exit(1);
    }

    // listen for client
    if(listen(serverSocket , 5) < 0){

        perror("listen failed");
        exit(1);
    }

    printf("waiting for incoming connection...\n");

    // accept client connection
    clientSocket = accept(serverSocket ,
                        (struct sockaddr*)&clientAddress ,
                        &clientLength);

    printf("client connected.\n");

    // receive filename
    int bytesReceived =
        recv(clientSocket ,
             filename ,
             sizeof(filename) ,
             0);

    filename[bytesReceived] = '\0';

    printf("client requested file : %s\n",
            filename);

    // open file
    filepointer = fopen(filename , "r");

    // file not found
    if(filepointer == NULL){

        strcpy(buffer ,
                "File not found!\n");

        send(clientSocket ,
             buffer ,
             strlen(buffer) ,
             0);

        printf("[error] file not found.\n");
    }

    // send file content
    else{

        while((readBytes =
                fread(buffer ,
                      1 ,
                      sizeof(buffer) ,
                      filepointer)) > 0){

            send(clientSocket ,
                 buffer ,
                 readBytes ,
                 0);
        }

        printf("[success] file transfer completed.\n");

        fclose(filepointer);
    }

    // close sockets
    close(clientSocket);
    close(serverSocket);

    return 0;
}