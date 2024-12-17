#include "lib/common.h"
#include "lib/server.h"

int main(int argc, char **argv){
    //Creating socketFD that's using IPv4, TCP on protocol 0, wich is IP (Internet protocol)
    int serverFileDescryptor = socket(AF_INET, SOCK_STREAM, 0); 
    createServer(&serverFileDescryptor);

    //    char lastReceived[BUFFER_SIZE] = {'\0'};
    char *arrCopy = NULL;
    arrCopy = "\n\0";
	
	while(1){
        // arrCopy = lastReceived;
		serverResponseHandle(&serverFileDescryptor, &arrCopy);
        // strcpy(lastReceived, arrCopy);
	}

    close(serverFileDescryptor);

    return 0;
}
