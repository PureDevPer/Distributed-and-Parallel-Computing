Part_2_Parallel : mcOmp.o timing.o
	gcc -o Part_2_Parallel mcOmp.o timing.o -fopenmp

mcOmp.o : mcOmp.c
	gcc -c mcOmp.c

timing.o : timing.c
	gcc -c timing.c
