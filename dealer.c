#include <vector>
#include <utility>

#include "commonFunc.c"
#include <getopt.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;

bool verbose = false;		// verbose mode flag
double percentage = -1;		// default to invalid value
int opt, num_trials = -1;	// default to invalid value

vector<pair<pid_t, int>> results; //collects child process metadata

const char * const showStatus(int &s) 
	{
	switch (s) 
		{
		case 768: //actually not the TRIAL_SUCCESS constant defined in showStatus
			return "success";
		case 1024: //somewhy not TRIAL_FAILURE
			return "failure";
		default:
			printf("err %d\n", s);
			return "unexpected status code";
		}
	}

int main(int argc, char * const argv[]) {

	//read cmdline args
	while ((opt = getopt(argc, argv, "vp:n:")) != -1) 
		{
		switch (opt) 
			{
			case 'v':
				verbose = true;
				break;
			case 'p':
				percentage = atoi(optarg);		//convert to integer
				break;
			default:
				fprintf(stderr, "Unrecognized option %c\n", optarg);
				exit(EXIT_FAILURE);
			}
		}

	//validate that command line args are provided correctly by user

	if (optind >= argc)		
		printError("You need to specify the number of trials to run!");

	if (percentage == -1)	// percentage not given
		printError("You need to specify a percentage!");

	num_trials = atoi(argv[optind]);	// convert numTrials to integer

	if (num_trials == -1)	// error
		printError("You need to specify a number of trials to run!");


	//spawn child hand processes
	
	pid_t child_pid;
	int child_status;
	for (size_t i = 0; i < num_trials; i++) 
		{
		if ((child_pid = fork()) < 0)
			fprintf(stderr, "Child process failed to execute.");
		if (child_pid == 0) 
			{
			execv("./hand", argv);
			_exit(1);		 
			} 
		else 
			{	
			wait(&child_status);
			results.push_back(make_pair(child_pid, child_status));
			}
		}

	//display results
	if (verbose) 
		{
		for (pair<pid_t, int> p : results)
			printf("PID %d returned %s.\n", p.first, showStatus(p.second));
		printf("\n");
		}

	printf("Created %d processes.\n", num_trials);

	//tally successes and failures
	double successes = 0, failures = 0;
	for (pair<pid_t, int> p : results) 
		{
		switch (p.second) 
			{
			case 768:  	// success exit code returned by child
				successes++;
				break;
			case 1024:	// failure exit code returned by child
				failures++;
				break;
			}
		}

	// display percentage of successes and failures
	printf("Success - %.2f%%\nFailure - %.2f%%\n", successes / num_trials * 100, failures / num_trials * 100);

	return EXIT_SUCCESS;
}

