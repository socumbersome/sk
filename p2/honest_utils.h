#ifndef __HONEST_UTILS_H_
#define __HONEST_UTILS_H_

#define REP(x, n) for(int x=0; x<(n); ++x)
#define FOR(x, b, e) for(int x=b; x<=(e); ++x)


#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>
#include "setup.h"

#define ERROR(str) { fprintf(stderr, "%s: %s\n", str, strerror(errno)); exit(1); }

typedef unsigned int uint;

time_t timespecToMs(struct timespec t);
struct timespec diffTime(struct timespec end, struct timespec start);
struct timeval MsToTimeval(time_t ms);
bool waitingTooLong(struct timespec startTime, int threshold, time_t* diffTimeMs);

#endif
