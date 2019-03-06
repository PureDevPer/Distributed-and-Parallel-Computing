// Wooseok Kim
// Homework #4

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <omp.h>
#include "timing.h"

int proc;

void Cal(int msize);

int main(int argc, char*argv[])
{
	if(argc<3)
	{
		perror("\n Use the parameter\n");
		exit(-1);
	}

	// argv1: N - Matrix Size between 64 - 1000
	int matrixSize = atoi(argv[1]);
	// argv2: P - # of Times
	proc = atoi(argv[2]);
	//int array[matrixSize][matrixSize];
	int i, j;
	int proc1 = proc;
	int rand_num;
	srand((unsigned)time(NULL));
	rand_num = rand()%10 + 1;



	

	// Time measurement
	timing_start();
	
// Start OpenMP 
// i,j, and k have independent values which means that the values are not shared
// Create threads
#pragma omp parallel private(i, j) num_threads(proc)
	{
		int **array = (int**)malloc(sizeof(int *)*matrixSize);
#pragma omp for 
		for(i=0; i<matrixSize; ++i)
		{
			array[i] = (int *)malloc(sizeof(int)*matrixSize);
		}

#pragma omp for 
		for(i=0; i<matrixSize; ++i)
		{
			for(j=0; j<matrixSize; ++j)
			{
				array[i][j] = rand()%10 + 1;
				//int a = array[i][j];
				//printf("%d \t", a);
			}
			//printf("\n");
		}
			// For loop is parallelized using the schedule
			// When I measured the time, guided was faster than static and dynamic.
			#pragma omp for schedule(guided, proc)
			for(j=0; j<matrixSize; j = j + proc1)
			{
				array[j] = (int *)malloc(sizeof(int)*matrixSize);
			}


			for(i=0;i<matrixSize;++i)
				free(array[i]);

			free(array);
						
	}
	


	timing_stop();
	print_timing();

}
