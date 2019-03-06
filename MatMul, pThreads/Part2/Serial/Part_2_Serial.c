// Wooseok Kim
// Computer Science

#include <stdio.h>
#include <stdlib.h>
#include "timing.h"


void SumUpto(int number)
{
	int sum = 0;
	int i;
	// add 1~number
	for(i=0; i<number; ++i)
		sum = sum + number;
}


int main(int argc, char*argv[])
{
	if (argc < 3)
	{
		perror("\nUse the parameter\n");
		exit(-1);
	}

	// argv1: # of Times executed p
	int loop = atoi(argv[1]);
	// argv2: summing upto number
	int number = atoi(argv[2]);
	int i = 0;


	// Time measurement
	timing_start();
	// how many times does it loop
	for(i=0;i<loop;++i)
	{
		SumUpto(number);
	}
	timing_stop();

	print_timing();
	return 0;
}