#include <netinet/in.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <asm-generic/socket.h>
#include <sys/sendfile.h>
#include <arpa/inet.h>

#define IP "127.0.0.1"
#define PORT 8080
#define QUEUE_SIZE 50
