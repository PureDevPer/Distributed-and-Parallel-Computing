#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mpi.h"
#include "timing.h"

int main(int argc, char*argv[])
{
    
	int i, hits;
	int rank, size;
    double x, y, rns;


  	int loop = atoi(argv[1]);
    if(argc<2)
    {
        perror("\nUEnter the number of loops you want\n");
        exit(-1);
     }


    timing_start();
  	MPI_Init(&argc, &argv); 
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int buf_hits[size];
    int buf_loop[size];

    rns = 1.0/(double)RAND_MAX;


    if(rank != 0)
    {
        // Calculate Monte Carlo
    	for (i=0; i<loop; i++) {
	        x = (double)rand() * rns;
	        y = (double)rand() * rns;
	        if (x*x + y*y < 1) {
	            hits++;
	        }
	    }

	    for (i=0; i<size; i++) {
	    	// Send hits, loop
	    	MPI_Send(&hits, 1, MPI_INT, 0, rank, MPI_COMM_WORLD);
	    	MPI_Send(&loop, 1, MPI_INT, 0, rank, MPI_COMM_WORLD);
	    }
    }
    else
    {
    	for(i=0; i<size; i++) {
            // Save hits, loop to buf_hits, buf_loop respectively
    		MPI_Recv(&buf_hits[i], size, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    		MPI_Recv(&buf_loop[i], size, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    	}
    }


    // Check output
    /*
    if(rank == 0){
    	int countHits = 0; 
    	int countLoop = 0;

    	for(i = 0 ; i < size ; ++i){
    		countHits = countHits + buf_hits[i];
    		countLoop = countLoop + buf_loop[i];
    	}

    	double pi = ((double)countHits/(double)countLoop)*4.0;
    	printf("PI: %f\n", pi);
    }
    */


 
    timing_stop();
    print_timing(); 

//    printf("pi = %f\n", 4*(double)hits/loop);
    MPI_Finalize();


	return 0;
}