#include <string.h>

#ifndef POSTHANDLER_H
#define POSTHANDLER_H

int getContentLength(const char*);

void parseFormData(const char*);

#endif
