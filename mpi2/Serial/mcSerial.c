// Wooseok Kim
// Homework #4

#include "timing.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// This variable is calculated in order to measure the numbers inside a circle
int hits;

int main(int argc, char*argv[])
{
    int i;
    double x, y, rns;

    if(argc<2)
	{
	    perror("\nUEnter the number of loops you want\n");
	    exit(-1);
	 }
  	int loop = atoi(argv[1]);

    rns = 1.0/(double)RAND_MAX;

    timing_start();
    for (i=0; i<loop; i++) {
        x = (double)rand() * rns;
        y = (double)rand() * rns;
        if (x*x + y*y < 1) {
            hits++;
        }
    }
  	timing_stop();
  	print_timing();

//    printf("pi = %f\n", 4*(double)hits/loop);
    return 0;
}
