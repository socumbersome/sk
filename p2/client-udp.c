/* **********************
 * Patryk Kajdas
 * Nr indeksu: 258311
 *
 ************************/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include "honest_utils.h"
#include "sockwrap.h"
#include "setup.h"
#include "sending_utils.h"
#include "receiving_utils.h"
#include "parsing_utils.h"


int main (int argc, char** argv)
{
	if (argc != 4)
	{
		printf("Usage: client-udp <port> <filename> <file size in bytes>\n");
		exit(1);
	}

	int SocketFD = Socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	int fileSize;
	char *fileName, *port;
	parseArguments(argv + 1, &port, &fileSize, &fileName);
	struct sockaddr_in serverAddress;
	memset(&serverAddress, 0, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	
	struct addrinfo hints, *servinfo;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;
	GetAddrInfo("aisd.ii.uni.wroc.pl", port, &hints, &servinfo);
	serverAddress = *(struct sockaddr_in *)servinfo->ai_addr;
	freeaddrinfo(servinfo);
	
	/*
	Inet_pton(AF_INET, "156.17.4.30", &serverAddress.sin_addr); // address of aisd.ii.uni.wroc.pl
	serverAddress.sin_port = htons(port); // if we are allowed to cheat... 
	*/
	
	int numberOfParts = (int)(fileSize / PART_SIZE);
	if(fileSize % PART_SIZE != 0)
		numberOfParts++;
	
	char *Buffer = malloc(numberOfParts * PART_SIZE * sizeof(char));
	bool *IsPartDownloaded = malloc(numberOfParts * sizeof(bool));
	memset(IsPartDownloaded, false, numberOfParts * sizeof(bool));
	

	while(SendRequestForFile(SocketFD, &serverAddress, numberOfParts, IsPartDownloaded))
		Download(SocketFD, &serverAddress, IsPartDownloaded, Buffer);
	
	
	FILE *file = fopen(fileName, "w");
	if(file != NULL)
	{
		fwrite(Buffer, sizeof(char), fileSize, file);
	}
	fclose(file);
	
	free(Buffer);
	free(IsPartDownloaded);
	
	return 0;
}
