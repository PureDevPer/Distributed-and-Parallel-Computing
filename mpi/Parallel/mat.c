#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mat.h"

mat_struct *getMatInfo(char mat[], int matSize)
{
	mat_struct *matInfo = malloc(sizeof(mat_struct));
	matInfo->row = matSize;
	matInfo->col = matSize;
	matInfo->mat_data = malloc(matSize * sizeof(double*));
	for(int i = 0 ; i < matSize ; ++i)
		matInfo->mat_data[i] = malloc(matSize * sizeof(double));

	FILE* fp = fopen(mat, "r");

	for(int i = 0 ; i < matSize ; ++i){
		for(int j = 0 ; j < matSize ; ++j){
			if(!fscanf(fp, "%lf", &matInfo->mat_data[i][j]))
				break;
		}
	}

	fclose(fp);

	return matInfo;
}

void print_mat(mat_struct *matPrint, int matrixSize)
{
	for(int i = 0 ; i < matrixSize ; ++i){
		for(int j = 0 ; j < matrixSize ; ++j){
			printf("%lf\t", matPrint->mat_data[i][j]);
		}
		printf("\n");
	}
}

void write_mat(mat_struct *matWrite, int matrixSize)
{
	FILE* fp = fopen("output.txt", "w");

	for(int i = 0 ; i < matrixSize ; ++i){
		for(int j = 0 ; j < matrixSize ; ++j){
			fprintf(fp, "%lf\t", matWrite->mat_data[i][j]);
		}
		fprintf(fp, "\n");
	}

	fclose(fp);
}

void free_mat(mat_struct *makeFreeMat, int matrixSize)
{
	for(int i = 0 ; i < matrixSize ; ++i)
		free(makeFreeMat->mat_data[i]);

	free(makeFreeMat->mat_data);
	free(makeFreeMat);
}

double *matLinear(mat_struct *mat, int matrixSize, int numMatrix) {
    double *matrix = malloc(numMatrix * sizeof(double));
    for (int i = 0; i < matrixSize; i++) {
    	 
    	// memory copy (dest,              src,              size_t n)
        memcpy((i * matrixSize)+matrix, mat->mat_data[i], matrixSize * sizeof(double));
    }
    return matrix;
}

void print_mat_mpi(double *output, int matrixSize, int numMatrix)
{
	for(int i = 0 ; i < numMatrix ; ++i){
		printf("%lf\t", output[i]);

		if((i+1) % matrixSize == 0)
			printf("\n");
	}
}

void write_mat_mpi(double *output, int matrixSize, int numMatrix)
{
	FILE* fp = fopen("output.txt", "w");

	for(int i = 0 ; i < numMatrix ; ++i){
		fprintf(fp, "%lf\t", output[i]);

		if( (i+1) % matrixSize == 0)
			fprintf(fp, "\n");
	}

	fclose(fp);
}

