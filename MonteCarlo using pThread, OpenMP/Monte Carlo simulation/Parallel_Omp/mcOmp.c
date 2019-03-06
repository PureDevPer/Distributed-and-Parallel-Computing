// Wooseok Kim
// Homework #4

// Reentrant is used due to rand()
// Reentrant function : "A function whose effect, when called by two or more threads, 
// is guaranteed to be as if the threads each executed the function one after another in an undefined order, 
// even if the actual execution is interleaved." - Single UNIX Specification version 3
#define _REENTRANT
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <omp.h>
#include "timing.h"

// This variable is calculated in order to measure the numbers inside a circle
int hits;

int main(int argc, char*argv[])
{
    unsigned int state1, state2;
    int     i;
    double  x, y, rns;

    if(argc<3)
    {
        perror("\nUEnter the number of loops and threads you want\n");
        exit(-1);
     }
    int loop = atoi(argv[1]);
    int numThreads = atoi(argv[2]);

    
    rns = 1.0/(double)RAND_MAX;
    state1 = (unsigned int)times(NULL);

    timing_start();
// Start OpenMP
#pragma omp parallel private(x, y, state2) num_threads(numThreads) reduction(+:hits) shared(state1)
    {
// Criticial Section
#pragma omp critical
        state2 = rand_r(&state1);
        //printf("THR[%d] state1/state2 = %u/%u\n", omp_get_thread_num(), state1, state2);
#pragma omp for
        for (i=0; i<loop; i++) {
            x = (double)rand_r(&state2) * rns;
            y = (double)rand_r(&state2) * rns;

            //printf("THR[%d:%d] x,y/state,hits = %f,%f/%u,%d\n", omp_get_thread_num(), i, x, y, state2,hits);

            if (x*x + y*y < 1) {
                hits++;
            }
        }
    }
    timing_stop();
    print_timing();

//    printf("hits(%d), pi = %f\n", hits, (double)hits/loop * 4);
    return 0;
}
