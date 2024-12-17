#include <stdlib.h>
#include <stdio.h>
#include "posthandler.h"
#include <string.h>

int getContentLength(const char *headers){
	const char *contentLengthStr = strstr(headers, "Content-Length: ");
	if(contentLengthStr) {
		return atoi(contentLengthStr + strlen("Content-Length: "));
	}
	return 0;
}

void parseFormData(const char *body) {
	printf("RECEIVED FORM DATA: \n");
    char *data = strdup(body);
    char *token = strtok(data, "&");
    while(token) {
        char *key = strtok(token, "=");
        char *value = strtok(NULL, "=");
        if(key && value){
            printf("%s: %s\n", key, value);
        }
        token = strtok(NULL, "&");
    }
    free(data);
}


