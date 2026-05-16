#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>

#define PORT 8080
#define SIZE 1024
int main(){
    int clientSocket;
    struct sockaddr_in serverAddress;
    char filename[SIZE];
    char buffer[SIZE];
    int readBytes ;

    //socket creation 
    clientSocket = socket(AF_INET,SOCK_STREAM,0);
    if (clientSocket<0){
        perror("socket creation failed.\n");
        exit(1);//exit with failure;
    }

    // configure the server 
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

    //establish connection to server 
    if(connect(clientSocket,
        (struct sockaddr*)&serverAddress,
        sizeof(serverAddress))<0){
            perror("connection failed.\n");
        }
    printf("connected to the server.\n");
    printf("Enter the file name : ");
    scanf("%s",filename);
    
    send(clientSocket ,
        filename,
        strlen(filename),
        0);
    
    while((readBytes = read(clientSocket ,
                            buffer,
                            sizeof(buffer)))>0){
                                fwrite(buffer,
                                    1,
                                    readBytes,  
                                    stdout);
                            }
    printf("File transfer complete.\n");
    close(clientSocket);
    return 0;
}