all: generateSquareMatrix Part_1_Parallel

generateSquareMatrix:
	gcc -o generateSquareMatrix generateSquareMatrix.c
Part_1_Parallel:
	mpicc -std=gnu99 -o Part_1_Parallel mpi.c timing.c mat.c