Part_1_Parallel : GetNumbers.o timing.o ArrayStackImplement.o ArrayStackParallelMain.o
	gcc -o Part_1_Parallel GetNumbers.o timing.o ArrayStackImplement.o ArrayStackParallelMain.o -lpthread

GetNumbers.o : GetNumbers.c
	gcc -c GetNumbers.c

timing.o : timing.c
	gcc -c timing.c
ArrayStackImplement.o : ArrayStackImplement.c
	gcc -c ArrayStackImplement.c

ArrayStackParallelMain.o : ArrayStackParallelMain.c
	gcc -c ArrayStackParallelMain.c
