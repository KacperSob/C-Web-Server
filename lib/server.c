#include "server.h"
#include "common.h"
#include "fileintegration.h"

void createServer(int *serverFileDescryptor){
    struct sockaddr_in address; //Imports socket structure for IPv4

    socklen_t addrlen = sizeof(address);
    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    address.sin_addr.s_addr = 0;

    //bind the socket to an IP addr
    if(bind(*serverFileDescryptor, (struct sockaddr*)&address, sizeof(address)) != 0){
        perror("COULND'T RESOLVE THE IP ADDRESS\n");
		exit(EXIT_FAILURE);   
   	}

	if(listen(*serverFileDescryptor, QUEUE_SIZE) < 0){
		perror("LISTENING FAILED\n");
		exit(EXIT_FAILURE);
	}

    printf("LISTENING ON PORT %d\n", PORT);

}

void serverResponseHandle(int *serverFileDescryptor){
	char buffer[BUFFER_SIZE] = { 0 };

	int client_fd = accept(*serverFileDescryptor, 0, 0); // fd as in file descryptor

	if(client_fd < 0){
		perror("ACCEPTING FAILED\n");
		exit(EXIT_FAILURE);
	}

	recv(client_fd, buffer, 1024-1, 0);
	printf("REQUEST RECEIVED: \n%s\n", buffer);

	// SIMPLE SEND A RESPONSE
	/*
	char response[] = "HTTP/1.1 200 OK\r\nContent-Length: 13\r\nConnection: close\r\n\r\nHello, world!";
	for (int sent = 0; sent < sizeof(response); sent += send(client_fd, response+sent, sizeof(response)-sent, 0));
	*/
	char filePath[BUFFER_SIZE] = "./";
	sscanf(buffer, "GET /%s ", filePath + 2); // add "./"

	sendFileResponse(client_fd, filePath);

	printf("SENDING A RETURN\n");

	close(client_fd);
	memset(buffer, 0, BUFFER_SIZE);
}

