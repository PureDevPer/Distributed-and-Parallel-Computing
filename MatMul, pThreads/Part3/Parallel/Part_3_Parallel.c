// Wooseok Kim
// Computer Science

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "timing.h"

int proc;

// Matrix can be divided by using malloc
void *Cal(void *arg)
{
	int i, j;
	int msiz = *((int*)arg);


	int rand_num;
	srand((unsigned)time(NULL));
	rand_num = rand()%10 + 1;

	// 2x2 array -> Malloc
	int **array = (int**)malloc(sizeof(int *)*msiz);


	for(i=0; i<msiz; ++i)
	{
		array[i] = (int *)malloc(sizeof(int)*msiz);
	}

	// Save random values to 2x2 array
	for(i=0; i<msiz; ++i)
	{
		for(j=0; j<msiz; ++j)
		{
			array[i][j] = rand()%10 + 1;
			//int a = array[i][j];
			//printf("%d \t", a);
		}

		//printf("\n");
	}

	// Divide row using malloc
	for(i=0; i<msiz; i = i + proc)
	{
		array[i] = (int *)malloc(sizeof(int)*msiz);
	}


	for(i=0;i<msiz;++i){
		free(array[i]);
	}

	free(array);
	pthread_exit(NULL);
}


int main(int argc, char*argv[])
{
	// argv1: N - Matrix Size between 64 - 1000
	int matrixSize = atoi(argv[1]);
	// argv2: P - # of threads
	proc = atoi(argv[2]);

	int rc;
	int rand_num;
	pthread_t pth[proc];

	
	srand((unsigned)time(NULL));
	rand_num = rand()%10 + 1;

	int i,j;

	if (argc<3)
	{
		perror("\nUse the parameter\n");
		exit(-1);
	}


	// Time measurement
	timing_start();
	// Loop upto threads
	for(i=0;i<proc;i++)
	{
		// Thread creation
		rc = pthread_create(&pth[i], NULL, Cal, (void*)&matrixSize);

	}
			if(rc){
			printf("ERROR\n");
			exit(-1);
		}
	timing_stop();

	print_timing();

	for(i=0; i<proc; ++i)
	{
		pthread_join(pth[i], NULL);
	}

	pthread_exit(NULL);

	return 0;

}