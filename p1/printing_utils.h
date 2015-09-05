#ifndef __PRINTING_UTILS_H_
#define __PRINTING_UTILS_H_

#include <stdio.h>
#include <stdbool.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>
#include "honest_utils.h"

void printAMagnificentStar(int ttl);
void printOneHop(int ttl, int howMany, bool receivedAll, struct in_addr* addresses, float avgTime);

#endif
