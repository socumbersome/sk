/* **********************
 * Patryk Kajdas
 * Nr indeksu: 258311
 *
 ************************/



#include "receiving_utils.h"

char DatagramBuffer[MAX_DATAGRAM_LENGTH];

void Download(int SocketFD, struct sockaddr_in* serverAddress, bool* IsPartDownloaded, char* Buffer)
{
	struct timespec startTime, currentTime;
	clock_gettime(CLOCK_MONOTONIC, &startTime);
	
	time_t alreadyWaiting = 0;
	int start;
	while(alreadyWaiting < WAITING_TIME)
	{
		if(ReceivePart(SocketFD, serverAddress, Buffer, &start))
			IsPartDownloaded[(int)(start / PART_SIZE)] = true;
		
		clock_gettime(CLOCK_MONOTONIC, &currentTime);
		alreadyWaiting = timespecToMs(diffTime(currentTime, startTime));
	}
}

bool ReceivePart(int SocketFD, struct sockaddr_in* serverAddress, char* Buffer, int *start)
{
	struct sockaddr_in addressResponded;
	socklen_t socketLength = sizeof(addressResponded);
	
	int n = recvfrom(SocketFD, DatagramBuffer, MAX_DATAGRAM_LENGTH, MSG_DONTWAIT, 
		(struct sockaddr *)&addressResponded, &socketLength);
	if((n < 0 && (errno == EAGAIN || errno == EWOULDBLOCK)) || 
		addressResponded.sin_addr.s_addr != serverAddress->sin_addr.s_addr ||
		addressResponded.sin_port != serverAddress->sin_port)
		return false;
	
	int headerLength;
	int dataLength;
		// %n number of characters read so far
	sscanf(DatagramBuffer, "DATA %d %d%n", start, &dataLength, &headerLength);
	
	
	memcpy(Buffer + *start, DatagramBuffer + headerLength + 1, dataLength);
	
	return true;
}
