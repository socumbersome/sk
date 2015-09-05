/* **********************
 * Patryk Kajdas
 * Nr indeksu: 258311
 *
 ************************/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "sockwrap.h"
#include "icmp.h"
#include "setup.h"
#include "sending_utils.h"
#include "receiving_utils.h"
#include "printing_utils.h"
#include "honest_utils.h"


int main (int argc, char** argv)
{
	if (argc != 2)
	{
		printf("Usage: traceroute <ip_address>\n");
		exit(1);
	}

	int SendingSocketFD = Socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	int ReceivingSocketFD = Socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	
	struct sockaddr_in destinationAddress;
	memset(&destinationAddress, 0, sizeof(destinationAddress));
	destinationAddress.sin_family = AF_INET;
	Inet_pton(AF_INET, argv[1], &destinationAddress.sin_addr);
	
	struct in_addr addressesResponded[PACKETS];
	float averageTimes[MYMAXTTL+1];
	memset(&averageTimes, 0, sizeof(averageTimes));
	
	struct timespec timeLeft;
	struct timespec now;
	struct timespec onesec;
	onesec.tv_sec = 1; onesec.tv_nsec = 0;
	struct timespec pastTime; //lol
	FOR(ttl, 1, MYMAXTTL)
	{
		struct timespec sendTime;
		sendTime = SendPackets(PACKETS, ttl, SendingSocketFD, &destinationAddress);
		
		bool destinationReached;
		int howManyReceived = ReceivePackets(ttl, ReceivingSocketFD, &averageTimes[ttl], \
			sendTime, &destinationReached, addressesResponded);
		
		if(howManyReceived == 0)
		{
			printAMagnificentStar(ttl);
			continue;
		}
		
		int uniques = makeUniqueAddresses(howManyReceived, addressesResponded);
		bool receivedAll = (howManyReceived == PACKETS);
		printOneHop(ttl, uniques, receivedAll, addressesResponded, averageTimes[ttl]);
		
		if(destinationReached)
			break;
		
		// no idea why it was included in specification - the faster the better, inn'it?
		clock_gettime(CLOCK_MONOTONIC, &now);
		pastTime = diffTime(now, sendTime);
		timeLeft = diffTime(onesec, pastTime);
		if(timeLeft.tv_sec >= 0)
			nanosleep(&timeLeft, NULL);
	}
	
	return 0;
}
