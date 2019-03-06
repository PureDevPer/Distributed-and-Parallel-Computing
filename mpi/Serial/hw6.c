#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "mat.h"
#include "timing.h"

// Number of matrix rows or columns
// The number of rows and columns are the same
int matrixSize;

int main(int argc, char *argv[])
{
	matrixSize = atoi(argv[3]);

	timing_start();
	// The matrix should be read from a text file
	mat_struct *input1 = getMatInfo(argv[1], matrixSize);
	mat_struct *input2 = getMatInfo(argv[2], matrixSize);

	if(argc < 4){
		perror("\nargv[1], [2] = matrix\nargv[3]: MatrixSize");
		exit(-1);
	}

	mat_struct *output = malloc(sizeof(mat_struct));
	output->mat_data = malloc(matrixSize * sizeof(double*));

	for(int i = 0 ; i < matrixSize ; ++i)
		output->mat_data[i] = malloc(matrixSize * sizeof(double));

	// Calculate output matrix
	int r;
	for(int i = 0 ; i < matrixSize ; ++i){
		for(int j = 0 ; j < matrixSize ; ++j){
			r = input1->mat_data[j][i];
			for(int k = 0 ; k < matrixSize ; ++k){
				output->mat_data[j][k] += r*input2->mat_data[i][k];
			}
		}
	}

    timing_stop();
    print_timing(); 

	//print_mat(output, matrixSize);
	write_mat(output, matrixSize);

	free_mat(input1, matrixSize);
	free_mat(input2, matrixSize);
	free_mat(output, matrixSize);

	return 0;
}
