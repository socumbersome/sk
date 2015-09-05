/* **********************
 * Patryk Kajdas
 * Nr indeksu: 258311
 *
 ************************/



#include "sending_utils.h"

struct timespec SendPackets(int howMany, int ttl, int SendingSocketFD, struct sockaddr_in* destinationAddr)
{
	struct timespec t;
	// I assume the loop below will execute very fast so instead of remembering timestamps for each packet
	// there will be only one, stamped just before the loop - should be sufficient
	clock_gettime(CLOCK_MONOTONIC, &t);
	
	REP(i, howMany)
	{
		struct icmp icmp_packet;
		icmp_packet.icmp_type = ICMP_ECHO;
		icmp_packet.icmp_code = 0;
		icmp_packet.icmp_id = (getpid() & 0xffff);
		icmp_packet.icmp_seq = (ttl << SEQ_SHIFT) | i; // now each sequence number is unique
			// and moreover we can extricate ttl from it later on! Whooa! Life is beautiful! \o/
		icmp_packet.icmp_cksum = 0; // no idea why
		// no idea why 8 and 0 as last arguments - copied from MBi's code...
		icmp_packet.icmp_cksum = in_cksum((ushort *)&icmp_packet, 8, 0);
		
		Setsockopt(SendingSocketFD, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl));
		Sendto(SendingSocketFD, &icmp_packet, ICMP_HEADER_LEN, 0, \
			&(*destinationAddr), sizeof(*destinationAddr));
	}
	return t;
}
