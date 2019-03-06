// Wooseok Kim
// Computer Science

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
  FILE *fp;
  int matrixSize = atoi(argv[1]), i, j, k;
  double min=0.00001, max=100000;;
  char comma[2];
  fp = fopen("inputMatrix.csv", "w");
  srand(time(NULL));
  fprintf(fp, "%d\n", matrixSize);
  double array[matrixSize][matrixSize];
  double array2[matrixSize][matrixSize];
  double array3[matrixSize][matrixSize];
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
      array4[i][j] = getRand(min, max);
      fprintf(fp, "%s%f",comma,d);
      sprintf(comma, "%s", ",");
      array3[i][j]=0;

      array2[i][j] = 0;
    }
      fprintf(fp, "\n");
  }

  fclose(fp);

  // Naive Implement
    timing_start();
    for(i=0;i<matrixSize;++i){
      for(j=0;j<matrixSize;++j){
        for(k=0;k<matrixSize;++k){
          array3[i][j] = array3[i][j] + array[i][k] * array4[k][j];
        }
    }
  }
  timing_stop();
  print_timing();

  // Move column in order to speed up
  int r;
    timing_start();
    for(k=0;k<matrixSize;++k){
      for(i=0;i<matrixSize;++i){
        r = array[i][k];
        for(j=0;j<matrixSize;++j){
          array2[i][j] += r*array4[k][j];
        }
    }
  }
  timing_stop();
  print_timing();


}


double getRand(double min, double max)
{
    double d = (double)rand() / RAND_MAX;
    return min + d * (max - min);
}