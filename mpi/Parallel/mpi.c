#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mpi.h"
#include "mat.h"
#include "timing.h"

// Number of matrix rows or columns
// The number of rows and columns are the same
int matrixSize;
// Number of matrix. 
// Since the number of rows and columns are the same, 
// the number of matrix can be calculated like below: matrixSize*matrixSize
int numMatrix;


int main(int argc, char *argv[]) {
    int matInfo[4], size, rank;
    double *input1, *input2, *output;
    
    
    matrixSize = atoi(argv[3]);
    numMatrix = matrixSize * matrixSize;

    if(argc < 4){
        perror("\nargv[1], [2] = matrix\nargv[3]: MatrixSize");
        exit(-1);
    }

    timing_start();
    
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    
    if (rank == 0) {
        
        if(argc < 4){
            perror( "\nargv[1], [2] = matrix\nargv[3]: MatrixSize");
            exit(-1);
        }
        



        // Read the same matrix input file as the one used in the serial program        
        mat_struct *gotMatInfo1 = getMatInfo(argv[1], matrixSize);
        mat_struct *gotMatInfo2 = getMatInfo(argv[2], matrixSize);

        // 2 Diemnsional matrix should change to 1 Dimensional matrix
        // Therefore, input1 and input2 matrix become 1 Dimensional matrix from 2 Dimensional matrix
        input1 = matLinear(gotMatInfo1, matrixSize, numMatrix);
        input2 = matLinear(gotMatInfo2, matrixSize, numMatrix);

        // Matrix rows and cols save respectively
        matInfo[0] = gotMatInfo1->row;
        matInfo[1] = gotMatInfo1->col;
        matInfo[2] = gotMatInfo2->row;
        matInfo[3] = gotMatInfo2->col;

        free_mat(gotMatInfo1, matrixSize);
        free_mat(gotMatInfo2, matrixSize);
    }

    // send the matrix information regarding rows and cols
    //MPI_Bcast(&buf, cnt, datatype,root, comm)
    MPI_Bcast(&matInfo, 4, MPI_INT, 0, MPI_COMM_WORLD);

    
    // Master - Prepare for calculating output matrix
    if(rank == 0) {
        output = malloc(numMatrix * sizeof(double));
    } 
    // If Master is not, two input matrices should be calculated
    else {
        input1 = malloc(numMatrix * sizeof(double));
        input2 = malloc(numMatrix * sizeof(double));
    }

    // send 1Dimensional matrices, input1 and input2
    //MPI_Bcast(&buf,    cnt,      datatype, root, comm)
    MPI_Bcast(input1, numMatrix , MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(input2, numMatrix , MPI_DOUBLE, 0, MPI_COMM_WORLD);
    
    
    int numRow = numMatrix / size;
    int startrow = (matrixSize / size) * rank;
    int endrow = ((matrixSize / size)*(rank + 1)) -1;    
    double *mat1Dimension = malloc(numRow * sizeof(double));

    int count = 0;

    // 1 Dimensional matrices are calculated 
    // and then calculated values are saved in mat1Dimension array
    for (int i = startrow; i <= endrow; ++i) {
        for (int j = 0; j < matrixSize; ++j) {
            for (int k = 0; k < matrixSize; ++k) {
                int argu1 = i * matrixSize + k;
                int argu2 = k * matrixSize + j;
                mat1Dimension[count] += input1[argu1]*input2[argu2];
            }
            ++count;
        }
    }
    

    
    // Gathers distinct values 
    // MPI_Gather(&sendbuf,   sendcnt, sendtype, &recvbuf, recvcnt, recvtype, root, comm)
    MPI_Gather(mat1Dimension, numRow, MPI_DOUBLE, output, numRow,  MPI_DOUBLE, 0, MPI_COMM_WORLD);

    timing_stop();
    print_timing(); 

    // Master - Save output as output.txt
    if (rank == 0){
        //print_mat_mpi(output, matrixSize, numMatrix);
        write_mat_mpi(output, matrixSize, numMatrix);
    }
    

    free(input1);
    free(input2);
    free(mat1Dimension);
    free(output);
    
    MPI_Finalize();
    return 0;
}



