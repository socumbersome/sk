#ifndef __PARSING_UTILS_H_
#define __PARSING_UTILS_H_

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

void parseArguments(char **argv, char **port, int *fileSize, char **fileName);

#endif
