// Wooseok Kim
// Computer Science

#include <stdio.h>
#include <stdlib.h>
#include "timing.h"

int proc;

// Matrix can be divided by using malloc
void Cal(int msize)
{
	int i, j;
	int rand_num;
	srand((unsigned)time(NULL));
	rand_num = rand()%10 + 1;

	// 2x2 array -> Malloc
	int **array = (int**)malloc(sizeof(int *)*msize);


	for(i=0; i<msize; ++i)
	{
		array[i] = (int *)malloc(sizeof(int)*msize);
	}

	// Save random values to 2x2 array
	for(i=0; i<msize; ++i)
	{
		for(j=0; j<msize; ++j)
		{
			array[i][j] = rand()%10 + 1;
			//int a = array[i][j];
			//printf("%d \t", a);
		}

		//printf("\n");
	}

	// Divide row using malloc
	for(i=0; i<msize; i = i + proc)
	{
		array[i] = (int *)malloc(sizeof(int)*msize);
	}


	for(i=0;i<msize;++i)
		free(array[i]);

	free(array);
}


int main(int argc, char* argv[])
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
	int array[matrixSize][matrixSize];
	int i;
	
	// Time measurement
	timing_start();
	// Loop upto P
	for(i=0; i<proc; ++i)
	{
		Cal(matrixSize);
	}
	timing_stop();

	print_timing();


}