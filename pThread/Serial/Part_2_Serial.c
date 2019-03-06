// Wooseok Kim
// Computer Science
// Homework #2

#include<stdio.h>
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include "timing.h"

double getRand(double min, double max);



int main(int argc, char*argv[])
{
  if(argc<2)
  {
    perror("\nUsage ./generateInput <squareMatrixSize>\n");
    exit(-1);
  }

  int matrixSize = atoi(argv[1]), i, j, k;

  // Time measurement start
  timing_start();
  // fp - inputMatrix
  // fp1 - inputMatrix1
  // fp2 - outputMatrix
  FILE *fp, *fp1, *fp2;
  double min=0.00001, max=100000;;
  char comma[2];
  fp = fopen("inputMatrix.csv", "w");
  fp1 = fopen("inputMatrix1.csv", "w");
  fp2 = fopen("outputMatrix.csv", "w");
  srand(time(NULL));
  fprintf(fp, "%d\n", matrixSize);
  fprintf(fp1, "%d\n", matrixSize);
  fprintf(fp2, "%d\n", matrixSize);

  // inputMatrix
  double array[matrixSize][matrixSize];
  // inputMatrix 1
  double array2[matrixSize][matrixSize];
  // ouputMatrix
  double array4[matrixSize][matrixSize];


  // Array creation which has random values 
  // (Used generateSquareMatrix file)
  for(i=0;i<matrixSize;i++)
  {
    sprintf(comma, "%s", "");
    for(j=0;j<matrixSize;j++)
    {
      double d = getRand(min, max);
      array[i][j] = d;
      double d1 = getRand(min, max);
      array4[i][j] = d1;
      fprintf(fp, "%s%f",comma,d);
      fprintf(fp1, "%s%f",comma,d1);
      sprintf(comma, "%s", ",");

      array2[i][j] = 0;
    }
      fprintf(fp, "\n");
      fprintf(fp1, "\n");
  }

  fclose(fp);
  fclose(fp1);

  // Move columns in order to speed up
  int r;

    for(k=0;k<matrixSize;++k){
      for(i=0;i<matrixSize;++i){
        r = array[i][k];
        for(j=0;j<matrixSize;++j){
          array2[i][j] += r*array4[k][j];
        }
    }
  }

  // End of time measurement
  timing_stop();
  print_timing();

  // Write outputMatrix
  for(i=0;i<matrixSize;++i){
  	sprintf(comma, "%s", "");
  	for(j=0;j<matrixSize;++j){
  		fprintf(fp2, "%s%f",comma,array2[i][j]);
  		sprintf(comma, "%s", ",");
  	}
  	fprintf(fp2, "\n");
  }

  fclose(fp2);

}


double getRand(double min, double max)
{
    double d = (double)rand() / RAND_MAX;
    return min + d * (max - min);
}