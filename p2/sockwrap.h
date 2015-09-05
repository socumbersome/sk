#ifndef __SOCKWRAP_H_
#define __SOCKWRAP_H_

#include <arpa/inet.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include "honest_utils.h"

int Socket(int family, int type, int protocol);
void Bind(int fd, const struct sockaddr_in *sa, socklen_t salen);
ssize_t Recvfrom (int fd, void *ptr, size_t nbytes, int flags, struct sockaddr_in *sa, socklen_t *salenptr);
bool Recv(int sockfd, void *buf, int len, int flags);
bool RecvTimeout(int sockfd, void *buf, int len, int flags, time_t timeoutInMs);
void Sendto(int fd, const void *ptr, int nbytes, int flags, const struct sockaddr_in *sa, socklen_t salen);
void Setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen);
int Select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);
void Inet_pton(int af, const char *src, void *dst);
void GetAddrInfo(const char *nodename, const char *servname, const struct addrinfo *hints, struct addrinfo **res);
#endif
