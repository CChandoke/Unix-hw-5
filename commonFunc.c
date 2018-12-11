#ifndef COMMON_FUNC
#define COMMON_FUNC

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//exit values
#define TRIAL_SUCCESS 3
#define TRIAL_FAILURE 4

//print an error message to stderr then exit
void printError(const char * const msg) 
	{
	fprintf(stderr, "%s\n", msg);
	exit(EXIT_FAILURE);
	}
	
#endif

