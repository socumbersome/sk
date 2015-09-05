#ifndef __RECEIVING_UTILS_H_
#define __RECEIVING_UTILS_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>
#include "honest_utils.h"
#include "sockwrap.h"

#define MAX_DATAGRAM_LENGTH 65535

void Download(int SocketFD, struct sockaddr_in* serverAddress, bool* IsPartDownloaded, char* Buffer);

bool ReceivePart(int SocketFD, struct sockaddr_in* serverAddress, char* Buffer, int *start);

#endif
