/* **********************
 * Patryk Kajdas
 * Nr indeksu: 258311
 *
 ************************/


#include "parsing_utils.h"

void parseArguments(char **argv, char **port, int *fileSize, char **fileName)
{
	char *pport = argv[0];
	while(*pport)
	{
		if(isdigit(*pport) == 0)
		{
			printf("Incorrect port number\n");
			exit(1);
		}
		pport++;
	}
	*port = argv[0];
	
	*fileName = argv[1];
	
	int scanres = sscanf(argv[2], "%d", fileSize);
	if(scanres == 0 || scanres == EOF || *fileSize < 0)
	{
		printf("Incorrect file size\n");
		exit(1);
	}
	
}
