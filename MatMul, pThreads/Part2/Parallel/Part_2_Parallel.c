// Wooseok Kim
// Computer Science

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "timing.h"


void *SumUpto(void *arg)
{
	int sum = 0;
	int number = *((int *)arg);
	int i;
	for(i=0; i<number; ++i)
		sum = sum + number;

	pthread_exit (NULL);
}




int main(int argc, char*argv[])
{
	if (argc < 3)
	{
		perror("\nUse the parameter\n");
		exit(-1);
	}

	// argv1: # of threads
	int NUM_THREADS = atoi(argv[1]);
	// argv2: Summing upto this number
	int number = atoi(argv[2]);
	int i = 0, rc;
	pthread_t pth[NUM_THREADS];

	// Time Measurement
	timing_start();
	// How many times does it make the thread
	for(i=0;i<NUM_THREADS;++i)
	{	// Thread creation
		rc = pthread_create(&pth[i], NULL, SumUpto, (void*)&number);

	}
	
		if(rc){
			printf("ERROR\n");
			exit(-1);
		}
	timing_stop();

	print_timing();

	pthread_exit(NULL);
	return 0;
}