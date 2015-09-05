/* **********************
 * Patryk Kajdas
 * Nr indeksu: 258311
 *
 ************************/



#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdlib.h>
#include "sockwrap.h"

#define ERROR(str) { fprintf(stderr, "%s: %s\n", str, strerror(errno)); exit(1); }

int Socket(int family, int type, int protocol)
{
	int	n;
	if ( (n = socket(family, type, protocol)) < 0)
		ERROR ("socket error");
	return n;
}

void Bind(int fd, const struct sockaddr_in *sa, socklen_t salen)
{
	if (bind(fd, (struct sockaddr*)sa, salen) < 0)
		ERROR ("bind error");
}

ssize_t Recvfrom(int fd, void *ptr, size_t nbytes, int flags, struct sockaddr_in *sa, socklen_t *salenptr)
{
	ssize_t	n;
	if ( (n = recvfrom(fd, ptr, nbytes, flags, (struct sockaddr*)sa, salenptr)) < 0)
		ERROR ("recvfrom error");
	return n;
}

bool Recv(int sockfd, void *buf, int len, int flags)
{
	int n =  recv(sockfd, buf, len, flags);
	if( n < 0 )
		ERROR ("recv error");
	return true;
}

bool RecvTimeout(int sockfd, void *buf, int len, int flags, time_t timeoutInMs)
{
	// copied from Beej's Guide to Network Programming
	fd_set fds;
	int n;
	struct timeval tv;
	
	FD_ZERO(&fds);
	FD_SET(sockfd, &fds);
	
	tv = MsToTimeval(timeoutInMs);
	n = select(sockfd + 1, &fds, NULL, NULL, &tv);
	
	if(n > 0)
		return Recv(sockfd, buf, len, flags);
		
	return false;
}

void Sendto(int fd, const void *ptr, int nbytes, int flags, const struct sockaddr_in *sa, socklen_t salen)
{
	if (sendto(fd, ptr, nbytes, flags, (struct sockaddr*)sa, salen) != nbytes)
		ERROR ("sendto error");
}

void Setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen)
{
	if (setsockopt(sockfd,level,optname,optval,optlen) < 0) 
		ERROR ("setsockopt error");
}

int Select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout)
{
	int n;
	if ((n = select(nfds,readfds,writefds,exceptfds,timeout)) < 0) 
		ERROR ("select error");
	return n;
}

void Inet_pton(int af, const char *src, void *dst)
{
	int n;
	if ((n = inet_pton(af, src, dst)) <= 0)
		ERROR ("not a valid IP address");
	
}

void GetAddrInfo(const char *nodename, const char *servname, const struct addrinfo *hints, struct addrinfo **res)
{
	if(getaddrinfo(nodename, servname, hints, res))
	{
		printf("Couldn't find %s\n", nodename);
		exit(1);
	}
	// OK
}
