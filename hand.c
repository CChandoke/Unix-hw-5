#include <getopt.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "gsl/gsl_rng.h"		// quotes -- search locally instead of in usr/lib, etc.
#include "commonFunc.c"

int main(int argc, char * const argv[]) {

	//initialize/declare vars

	int opt;
	unsigned percentage = -1;

	//read cmdline args

	while ((opt = getopt(argc, argv, "p:")) != -1) {
		switch (opt) {
			case 'p':
				percentage = atoi(optarg);
				break;
			default:
				fprintf(stderr, "Usage: %s -p <percentage>\n", argv[0]);
				exit(EXIT_FAILURE);
		}
	}

	if (percentage == -1)
		printError("You need to specify a percentage!");

	//main functionality

	gsl_rng *rng = gsl_rng_alloc(gsl_rng_mt19937);
	struct timespec tp;
	clock_gettime(CLOCK_REALTIME, &tp);
	gsl_rng_set(rng, tp.tv_nsec);
	if (rng == NULL)
		printError("Failed to initialize GSL random number generator! Aborting.");

	double randVal = gsl_rng_uniform (rng) * 100;
	gsl_rng_free (rng);

	if (randVal <= percentage) {
		//printf("success!\n"); //testing
		exit(TRIAL_SUCCESS);
	} else {
		//printf("failure!\n"); //testing
		exit(TRIAL_FAILURE);
	}
}

