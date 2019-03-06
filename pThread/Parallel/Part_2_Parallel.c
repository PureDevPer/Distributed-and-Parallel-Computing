// Wooseok Kim
// Computer Science
// Homework #2

#include<stdio.h>
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include <pthread.h>
#include "timing.h"

double getRand(double min, double max);

pthread_mutex_t mutex;
pthread_cond_t cond;



void *Cal(void *matrixSize1)
{
  int i,j,k;
  int matrixSize = *((int*)matrixSize1);

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


  // malloc
  // Create arrays by using malloc
  double **inputArray, **inputArray2, **outputArray;
  inputArray = (double **)malloc(matrixSize * sizeof(double *));
  inputArray2 = (double **)malloc(matrixSize * sizeof(double *));
  outputArray = (double **)malloc(matrixSize * sizeof(double *));

  for(i=0; i<matrixSize; ++i){
    inputArray[i] = (double *)malloc(matrixSize * sizeof(double));
    inputArray2[i] = (double *)malloc(matrixSize * sizeof(double));
    outputArray[i] = (double *)malloc(matrixSize * sizeof(double));
  }


  // Array creation which has random values 
  // (Used generateSquareMatrix file)
  for(i=0;i<matrixSize;i++)
  {
    sprintf(comma, "%s", "");
    for(j=0;j<matrixSize;j++)
    {
      double d = getRand(min, max);
      inputArray[i][j] = d;
      double d1 = getRand(min, max);
      inputArray2[i][j] = d1;
      fprintf(fp, "%s%f",comma,d);
      fprintf(fp1, "%s%f",comma,d1);
      sprintf(comma, "%s", ",");
      outputArray[i][j]=0;
    }
      fprintf(fp, "\n");
      fprintf(fp1, "\n");
  }

  fclose(fp);
  fclose(fp1);

  // Move column in order to speed up
  int r;
  
  //pthread_mutex_lock(&mutex); 
  for(k=0;k<matrixSize;++k){
    for(i=0;i<matrixSize;++i){
      r = inputArray[i][k];
      for(j=0;j<matrixSize;++j){     
          outputArray[i][j] += r * inputArray2[k][j];
          
      }
    }
  }
  //pthread_mutex_unlock(&mutex);


  for(i=0;i<matrixSize;++i){
    sprintf(comma, "%s", "");
    for(j=0;j<matrixSize;++j){
      fprintf(fp2, "%s%f",comma,outputArray[i][j]);
      sprintf(comma, "%s", ",");
    }
    fprintf(fp2, "\n");
  }

  for(i=0;i<matrixSize;++i){
    free(inputArray[i]);
    free(inputArray2[i]);
    free(outputArray[i]);
  }

  free(inputArray);
  free(inputArray2);
  free(outputArray);
  fclose(fp2);

}



int main(int argc, char*argv[])
{
  if(argc<3)
  {
    perror("\nUsage ./generateInput <squareMatrixSize>\n");
    exit(-1);
  }
  int matrixSize = atoi(argv[1]), i, j, k;
  int NumThread = atoi(argv[2]);

  int rc;
  pthread_t pth[NumThread];
  //pthread_mutex_init(&mutex, NULL);
  //pthread_cond_init(&cond, NULL);


  // Time measurement
  timing_start();
  // Loop upto NumThread
  for(i=0;i<NumThread;i++)
  {
    rc = pthread_create(&pth[i], NULL, Cal, (void*)&matrixSize);

  }
    if(rc){
      printf("ERROR\n");
      exit(-1);
    }
    // End of time measurement
  timing_stop();

  print_timing();

  for(i=0;i<NumThread;i++)
  {
    pthread_join(pth[i], NULL);
  }



}


double getRand(double min, double max)
{
    double d = (double)rand() / RAND_MAX;
    return min + d * (max - min);
}