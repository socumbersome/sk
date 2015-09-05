#ifndef __SENDING_UTILS_H_
#define __SENDING_UTILS_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include "sockwrap.h"
#include "honest_utils.h"

char RequestBuffer[20];

bool SendRequestForFile(int SocketFD, struct sockaddr_in* serverAddress, int numberOfParts, bool* IsPartDownloaded);

void SendRequestForPart(int SocketFD, struct sockaddr_in* serverAddress, int from);

#endif
