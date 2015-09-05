/* **********************
 * Patryk Kajdas
 * Nr indeksu: 258311
 *
 ************************/



#include "sending_utils.h"

bool SendRequestForFile(int SocketFD, struct sockaddr_in* serverAddress, int numberOfParts, bool* IsPartDownloaded)
{
	bool somethingSent = false;
	REP(i, numberOfParts)
		if(!IsPartDownloaded[i])
		{
			somethingSent = true;
			SendRequestForPart(SocketFD, serverAddress, i * PART_SIZE);
		}
	
	return somethingSent;
}

void SendRequestForPart(int SocketFD, struct sockaddr_in* serverAddress, int from)
{
	sprintf(RequestBuffer, "GET %d %d\n", from, PART_SIZE);
	sendto(SocketFD, RequestBuffer, strlen(RequestBuffer), 0, (struct sockaddr*)serverAddress, sizeof(*serverAddress));
}
