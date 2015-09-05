#ifndef __HONEST_UTILS_H_
#define __HONEST_UTILS_H_

#define REP(x, n) for(int x=0; x<(n); ++x)
#define FOR(x, b, e) for(int x=b; x<=(e); ++x)

#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <netinet/ip_icmp.h>
#include "setup.h"

int IPHeaderBLen(struct ip* ipp);
time_t timespecToMs(struct timespec t);
struct timespec diffTime(struct timespec end, struct timespec start);
struct timeval MsToTimeval(time_t ms);
bool waitingTooLong(struct timespec startTime, int threshold, time_t* diffTimeMs);

int in_addrComparator(const void *x,  const void *y);
int makeUniqueAddresses(int howMany, struct in_addr* addresses);

#endif
