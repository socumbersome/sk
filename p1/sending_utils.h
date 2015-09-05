#ifndef __SENDING_UTILS_H_
#define __SENDING_UTILS_H_

#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include "icmp.h"
#include "sockwrap.h"
#include "honest_utils.h"

struct timespec SendPackets(int howMany, int ttl, int SendingSocketFD, struct sockaddr_in* destinationAddr);

#endif
