#ifndef __RECEIVING_UTILS_H_
#define __RECEIVING_UTILS_H_

#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include "honest_utils.h"
#include "sockwrap.h"
#include "icmp.h"

///#define NOTHING 0
//#define INTERMEDIATE 1
//#define DESTINATION 2

unsigned char packetBuffer[IP_MAXPACKET+1]; // IP_MAXPACKET comes from netinet/ip_icmp.h
	// and means - maximum packet size (no, that wasn't obvious oO)
unsigned char* packetBuffer_ptr;

int ReceivePackets(int ttl, int ReceivingSocketFD, float *averageTime, \
	struct timespec startTime, bool *destinationReached, struct in_addr* addressesResponded);

#endif
