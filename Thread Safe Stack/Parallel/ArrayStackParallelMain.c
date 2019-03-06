// Wooseok Kim
// Homework #3 - Parallel

#include "stackHw.h"
#include "timing.h"
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t *m;

pthread_cond_t *notFull;
pthread_cond_t *notEmpty;
ArrayStack* Stack = NULL;

// Push Thread
void *pushThread(void* St)
{
	int i,j;
	int ThreadLoop = *((int*)St);

	for(j=0;j<ThreadLoop;++j){
		while(!IsFull(Stack)){

			for(i=0; i<numSize; ++i){


				//pthread_mutex_lock(m);
				Push(Stack, numbers[i]);
				//printf("Push: %d\n", numbers[i]);
				//pthread_mutex_unlock(m);
			}
		}
	}
	pthread_exit(0);
}

// Pop Thread
void *popThread(void* St)
{
	int i,j;
	int ThreadLoop = *((int*)St);

	for(j=0;j<ThreadLoop;++j){
		for(i=0; i<numSize; ++i){

			if(IsEmpty(Stack))
				break;

			//pthread_mutex_lock(m);		
			Pop(Stack);
			//pthread_mutex_unlock(m);						
		}
	}
		pthread_exit(0);
}

int main(int argc, char*argv[])
{
	char file[] = "numbers.txt";
	GetNumbers(file);

	int i = 0,j;
	

	if(argc<3)
	{
	    perror("\nUEnter the number of loops you want\n");
	    exit(-1);
	 }

  	int numThread = atoi(argv[1]);
  	int loop = atoi(argv[2]);

	pthread_t PopThread[numThread];
	pthread_t PushThread[numThread];

	// Mutex
	(m) = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	// Condition variables
	(notFull) = (pthread_cond_t *)malloc(sizeof(pthread_cond_t));
	(notEmpty) = (pthread_cond_t *)malloc(sizeof(pthread_cond_t));

  	timing_start();

		for(i=0; i<numThread; ++i)
		{
			CreateStack(&Stack, numSize);
			pthread_create(&PushThread[i], NULL, pushThread, (void*)&loop);
			pthread_create(&PopThread[i], NULL, popThread, (void*)&loop);
		}

	for(i=0; i<numThread; ++i)
		{
			pthread_join(PushThread[i], NULL);
			pthread_join(PopThread[i], NULL);
		}
		DestroyStack(Stack);
  		
  	timing_stop();
  	print_timing();


  	pthread_mutex_destroy(m);

  	pthread_cond_destroy (notFull);
	pthread_cond_destroy (notEmpty);

  	free(m);
  	free(notFull);free(notEmpty);

	return 0;
}
