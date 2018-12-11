
#include <getopt.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <gsl/gsl_rng.h>
#include "commonFunc.c"

int main(int argc, char * const argv[]) {

	//initialize/declare vars

	int opt;
	size_t percentage = -1;

	//read cmdline args

	opterr = 0;		// set to 0 so getopt will ignore nonsense options 
					// rather than output error messages by default
	
	while ((opt = getopt(argc, argv, "p:")) != -1) 
		{
		switch (opt) 
			{
			case 'p':
				percentage = atoi(optarg);		// convert percentage to integer so we can compare it
				break;
			}
		}

	if (percentage == -1)	// error
		printError("You need to specify a percentage!");

	//main functionality

	gsl_rng *rng = gsl_rng_alloc(gsl_rng_mt19937);
	struct timespec tp;
	clock_gettime(CLOCK_REALTIME, &tp);		// used as seed for random number generator
	gsl_rng_set(rng, tp.tv_nsec);		// convert to nanoseconds (so seed is different for each 
										// child process) and generate random number
	if (rng == NULL)
		printError("Failed to initialize GSL random number generator! Aborting.");

	double randVal = gsl_rng_uniform (rng) * 100;	// convert to percentage
	gsl_rng_free (rng);		

	if (randVal <= percentage) 
		{		
		//printf("success!\n"); //testing
		exit(TRIAL_SUCCESS);
		} 
	else 
		{
		//printf("failure!\n"); //testing
		exit(TRIAL_FAILURE);
		}
}

