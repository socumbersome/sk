/* **********************
 * Patryk Kajdas
 * Nr indeksu: 258311
 *
 ************************/



#include "printing_utils.h"

void printAMagnificentStar(int ttl)
{
	printf("%d. *\n", ttl);
}

void printOneHop(int ttl, int howMany, bool receivedAll, struct in_addr* addresses, float avgTime)
{
	if(howMany > 0)
		printf("%d. ", ttl);
	REP(i, howMany)
	{
		char aux[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &addresses[i], aux, INET_ADDRSTRLEN);
		printf("%s  ", aux);
	}
	if(receivedAll)
		printf("%.2f ms", avgTime);
	else
		printf("???");
	printf("\n");
}
