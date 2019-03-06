// Wooseok Kim
// Homework #4

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include "timing.h"

// mutext initialization
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


static int loop;
double pi, step;

void *start_func(void *loopArg)
{
    long i;
    double x, y, rns;
    rns = 1.0/(double)RAND_MAX;
    long loop1 = *((int*)loopArg);
//    printf("%ld\n", loop1);

    // This variable is calculated in order to measure the numbers inside a circle
    int hits=0;

    for (i=0; i<loop1; i++) {
        
        x = (double)rand() * rns;
        y = (double)rand() * rns;
        if (x*x + y*y < 1) {
            hits++;
        }
        
    }
}

int main(int argc, char*argv[])
{

    if(argc<3)
    {
        perror("\nUEnter the number of loops and threads you want\n");
        exit(-1);
     }
    loop = atoi(argv[1]);
    int numThreads = atoi(argv[2]);

    int i;
    
    pthread_t pt_id[numThreads];



    timing_start();
    for (i=0; i<numThreads ; ++i) { 
        // create pthread
        if (pthread_create(&pt_id[i], NULL, start_func, (void*)&loop)){
            perror("pthread_create");
            return 0;
        }
    }
    timing_stop();
    print_timing();

    for (i=0; i<numThreads ; ++i) { 
    // join pthread
        if (pthread_join(pt_id[i], NULL)){
            perror("pthread_join");
            return 1;
        }
    }
    //sum = start_arg[0].sum + start_arg[1].sum;
    //printf("PI = %.8f (sum = %.8f)\n", step*sum, sum);
    return 0;
}
