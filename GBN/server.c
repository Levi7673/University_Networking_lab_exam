#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<time.h>
#include<unistd.h>

#define PORT 8080
#define SIZE 1024
#define ACK_PROB 70

int main(){

    int serverSocket , clientSocket;

    struct sockaddr_in serverAddress ,
                        clientAddress;

    socklen_t clientLength =
                sizeof(clientAddress);

    char receivedBuffer[SIZE];

    int receivedPacket;

    // socket creation
    serverSocket =
        socket(AF_INET,SOCK_STREAM,0);

    // configure socket
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    // random seed
    srand(time(0));

    // bind
    if(bind(serverSocket,
        (struct sockaddr*)&serverAddress,
        sizeof(serverAddress)) < 0){

        perror("bind failed");
        exit(1);
    }

    // listen
    if(listen(serverSocket,5) < 0){

        perror("listen failed");
        exit(1);
    }

    // accept connection
    clientSocket = accept(serverSocket,
                    (struct sockaddr*)&clientAddress,
                    &clientLength);

    printf("\n===========GO BACK N RECEIVER===========\n");
    printf("[connected] : sender connected.\n");

    while(1){

        memset(receivedBuffer,0,SIZE);

        int readBytes =
            read(clientSocket,
                receivedBuffer,
                SIZE);

        // sender finished
        if(readBytes <= 0){

            printf("[EXIT] : transmission complete.\n");
            break;
        }

        receivedPacket =
            atoi(receivedBuffer);

        printf("[RECEIVE] : packet %d received\n",
                receivedPacket);

        // ACK loss simulation
        if(rand()%100 < ACK_PROB){

            printf("[ACK LOST] : ACK lost for packet %d\n",
                    receivedPacket);
        }

        // send ACK
        else{

            sprintf(receivedBuffer,
                    "%d",
                    receivedPacket);

            send(clientSocket,
                receivedBuffer,
                strlen(receivedBuffer)+1,
                0);

            printf("[ACK] : ACK sent for packet %d\n",
                    receivedPacket);
        }
    }

    close(clientSocket);
    close(serverSocket);

    return 0;
}