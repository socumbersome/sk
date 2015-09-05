/* **********************
 * Patryk Kajdas
 * Nr indeksu: 258311
 *
 ************************/



#include "receiving_utils.h"

int ReceivePackets(int ttl, int ReceivingSocketFD, float *averageTime, \
	struct timespec startTime, bool *destinationReached, struct in_addr* addressesResponded)
{
	*averageTime = 0;
	*destinationReached = false;
	time_t whenReached = 0;
	time_t diffTimeMs = 0;
	int nbOfSuccesses = 0;
	while(nbOfSuccesses < PACKETS)
	{
		if(waitingTooLong(startTime, WAITING_TIME, &diffTimeMs))
			break;
		
		if(!RecvTimeout(ReceivingSocketFD, packetBuffer, IP_MAXPACKET, 0, WAITING_TIME))
			continue;
		
		if(waitingTooLong(startTime, WAITING_TIME, &diffTimeMs))
			break;
		
		packetBuffer_ptr = packetBuffer;
		struct ip* ip_packet = (struct ip*) packetBuffer_ptr;
		packetBuffer_ptr += IPHeaderBLen(ip_packet);
		struct icmp* icmp_packet = (struct icmp*) packetBuffer_ptr;
		packetBuffer_ptr += ICMP_HEADER_LEN;
		
		struct ip* ip_packet_orig = (struct ip*) packetBuffer_ptr;
		packetBuffer_ptr += IPHeaderBLen(ip_packet_orig); 
		struct icmp *icmp_packet_orig = (struct icmp*) packetBuffer_ptr;
		
		if (icmp_packet->icmp_type == ICMP_TIME_EXCEEDED
			&& icmp_packet->icmp_code == ICMP_EXC_TTL
			&& icmp_packet_orig->icmp_id == (getpid() & 0xffff)
			&& (icmp_packet_orig->icmp_seq >> SEQ_SHIFT) == ttl)
		{
			addressesResponded[nbOfSuccesses++] = ip_packet->ip_src;
		}
		else if(icmp_packet->icmp_type == ICMP_ECHOREPLY
			&& icmp_packet->icmp_id == (getpid() & 0xffff)
			&& (icmp_packet->icmp_seq >> SEQ_SHIFT) == ttl)
		{
			addressesResponded[nbOfSuccesses++] = ip_packet->ip_src;
			*destinationReached = true;
		}
		
		// even if haven't reached anything, it doesn't bother us
		// because we won't print the average time then
		whenReached += diffTimeMs;
	}
	if(nbOfSuccesses == PACKETS)
		*averageTime = whenReached * 1.0f / PACKETS;
	
	return nbOfSuccesses;
}
