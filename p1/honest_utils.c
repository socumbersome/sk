/* **********************
 * Patryk Kajdas
 * Nr indeksu: 258311
 *
 ************************/



#include "honest_utils.h"

int IPHeaderBLen(struct ip* ipp)
{ // because ip_hl keeps the number of four-Bytes in the total IP header length
	return (ipp->ip_hl * 4);
}

time_t timespecToMs(struct timespec t)
{
	return (t.tv_sec * 1000 + t.tv_nsec / 1000000);
}

// assertion: end >= start in lexicographic order. Implementation isn't idiot-proof.
struct timespec diffTime(struct timespec end, struct timespec start)
{
	struct timespec x;
	if(end.tv_nsec < start.tv_nsec)
	{
		x.tv_sec = end.tv_sec - 1 - start.tv_sec;
		x.tv_nsec = end.tv_nsec + 1000000000 - start.tv_nsec;
	}
	else
	{
		x.tv_sec = end.tv_sec - start.tv_sec;
		x.tv_nsec = end.tv_nsec - start.tv_nsec;
	}
	return x;
}

struct timeval MsToTimeval(time_t ms)
{
	struct timeval t;
	t.tv_sec = ms / 1000;
	t.tv_usec = (ms % 1000) * 1000;
	return t;
}

// sets diffTimeMs parameter as well (appalling...)
bool waitingTooLong(struct timespec startTime, int threshold, time_t* diffTimeMs)
{
	struct timespec endTime;
	clock_gettime(CLOCK_MONOTONIC, &endTime);
	*diffTimeMs = timespecToMs(diffTime(endTime, startTime));
	if(*diffTimeMs > threshold)
		return true;
	return false;
}

int in_addrComparator(const void *x,  const void *y)
{
	return (((struct in_addr *)x)->s_addr - ((struct in_addr *)y)->s_addr);
}

// returns the number of unique addresses
int makeUniqueAddresses(int howMany, struct in_addr* addresses)
{
	qsort(addresses, howMany, sizeof(*addresses), in_addrComparator);
	int uniques = 1;
	REP(i, howMany)
	{
		if(i == 0)
			continue;
		if(addresses[i - 1].s_addr != addresses[i].s_addr)
		{
			addresses[uniques] = addresses[i]; // I hope copying works with structs oO
			uniques++;
		}
	}
	
	return uniques;
}
