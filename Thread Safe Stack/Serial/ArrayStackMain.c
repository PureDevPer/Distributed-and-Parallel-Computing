// Wooseok Kim
// Homework #3 - Serial
#include "stackHw.h"
#include "timing.h"

int main(int argc, char*argv[])
{
	char file[] = "numbers.txt";
	GetNumbers(file);

	int i = 0,j;
	ArrayStack* Stack = NULL;

	if(argc<2)
	{
	    perror("\nUEnter the number of loops you want\n");
	    exit(-1);
	 }
  	int loop = atoi(argv[1]);

  	timing_start();
  	for(j=0; j<loop ;++j)
  	{
	  	CreateStack(&Stack, numSize);

		while(!IsFull(Stack)){
			for(i=0; i<numSize; ++i){
				Push(Stack, numbers[i]);
			}
		}

		

		for(i=0; i<numSize; ++i){
			if(IsEmpty(Stack))
				break;

			Pop(Stack);
		}

		DestroyStack(Stack);
  	}
  	timing_stop();
  	print_timing();

	return 0;
}