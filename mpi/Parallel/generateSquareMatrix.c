#include<stdio.h>
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include <string.h>
//prototype
double getRand(double min, double max);

int main(int argc, char*argv[])
{
  if(argc<2)
  {
    perror("\nUsage ./generateInput <squareMatrixSize>\n");
    exit(-1);
  }
  FILE *fp, *fp1;
  int matrixSize = atoi(argv[1]), i, j;
  char ch[10], ch1[10];
  strcpy(ch, argv[1]); strcpy(ch1, argv[1]);
  strcat(ch, ".txt"); strcat(ch1, "a.txt");
  double min=0.00001, max=100000;
  char comma[2];
  fp = fopen(ch, "w");
  fp1 = fopen(ch1, "w");
  srand(time(NULL));
  //fprintf(fp, "%d\n", matrixSize);
  for(i=0;i<matrixSize;i++)
  {
    sprintf(comma, "%s", "");
    for(j=0;j<matrixSize;j++)
    {
      fprintf(fp, "%f\t",getRand(min, max));
      fprintf(fp1, "%f\t",getRand(min, max));
      //sprintf(comma, "%s", ",");;
    }
      fprintf(fp, "\n");
      fprintf(fp1, "\n");
  }

  fclose(fp);
  fclose(fp1);

}


double getRand(double min, double max)
{
    double d = (double)rand() / RAND_MAX;
    return min + d * (max - min);
}
