#include "server.h"
#include "common.h"

void createServer(int *serverFileDescryptor){
    char buffer[1024] = { 0 };

    ssize_t valread;

    struct sockaddr_in address; //Imports socket structure for IPv4

    socklen_t addrlen = sizeof(address);
    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    address.sin_addr.s_addr = 0;

    //bind the socket to an IP addr
    if(bind(*serverFileDescryptor, (struct sockaddr*)&address, sizeof(address)) != 0){
        perror("COULND'T RESOLVE THE IP ADDRESS\n");
        abort();
    }

    listen(*serverFileDescryptor, QUEUE_SIZE);

    printf("LISTENING ON PORT %d\n", PORT);

    int client_fd = accept(*serverFileDescryptor, 0, 0); // fd as in file descryptor

    recv(client_fd, buffer, 1024-1, 0);

    // SIMPLE SEND A RESPONSE

    char response[] = "HTTP/1.1 200 OK\r\nContent-Length: 13\r\nConnection: close\r\n\r\nHello, world!";
    for (int sent = 0; sent < sizeof(response); sent += send(client_fd, response+sent, sizeof(response)-sent, 0));

    printf("SENDING A RETURN\n");

    close(client_fd);
}
