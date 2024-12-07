#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "common.h"

char *getContentType(const char* path){
	if (strstr(path, ".html")) return "text/html";
	if (strstr(path, ".css")) return "text/css";	
	if (strstr(path, ".js")) return "application/javascript";
	if (strstr(path, ".jpg") || strstr(path, ".jpeg")) return "image/jpeg";
	if (strstr(path, ".png")) return "image/png";
	return "application/octet-stream"; // default 
}

void sendFileResponse(int clientSocket, const char* filepath){
	printf("FILEPATH: \n%s\n", filepath);
	if(strcmp(filepath, "./") == 0 || strcmp(filepath, "./HTTP/1.1") == 0){
		filepath = "./index.html";
	}
	FILE *file = fopen(filepath, "rb");
	if(file == NULL) {
		// file not found sending 404;
		//file = fopen("index.html", "rb");
		
		//if(file == NULL){
			const char* notFound = "HTTP/1.1 404 Not Found\r\n"
							       "Content-Type: text/html\r\n\r\n"
								   "<html><body><h1>404 Not Found</h1></body></html>";
			send(clientSocket, notFound, strlen(notFound), MSG_NOSIGNAL);
			return;
		//}
		//fclose(file);
		//sendFileResponse(clientSocket, "/index.html");
		//return;
	}	
	
	fseek(file, 0, SEEK_END); // determines the file size
	long fileSize = ftell(file);
	rewind(file);


	char *fileBuffer = (char*)malloc(fileSize);
	fread(fileBuffer, 1, fileSize, file);
	fclose(file);
	
	// construct HTTP response header
	const char* contentType = getContentType(filepath);
	char header[BUFFER_SIZE];
	snprintf(header, sizeof(header), "HTTP/1.1 200 OK \r\n"
									 "Content-Type: %s\r\n"
									 "Content-Length: %ld\r\n\r\n", contentType, fileSize);
	
	// send the header
	send(clientSocket, header, strlen(header), MSG_NOSIGNAL);

	// send the content
	send(clientSocket, fileBuffer, fileSize, MSG_NOSIGNAL);

	printf("\n%s\n%s\n", header, fileBuffer);

	free(fileBuffer);
}

