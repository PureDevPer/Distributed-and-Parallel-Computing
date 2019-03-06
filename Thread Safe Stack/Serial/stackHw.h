// Wooseok Kim
// Homework #3 - Serial

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//Use these to change iterations and threads
#define NUM_THREADS 50
#define ITERATIONS 500

//globals 
extern int *numbers;
extern int numSize ;
//add More globals/etc below


//All functions
extern void GetNumbers(char fileName[]);

//You need to create all of the below functions
//extern long long GetStackCount(); 
//extern int Pop();
//extern void Push(int number);
//extern void PrintAll(); // optional



typedef int ElementType;

typedef struct tagNode{
	ElementType Data;
}Node;

typedef struct tagArrayStack
{
	int Top;
	int Capacity;
	Node* Nodes;
}ArrayStack;

void CreateStack(ArrayStack** Stack, int Capacity);
void DestroyStack(ArrayStack* Stack);
void Push(ArrayStack* Stack, ElementType Data);

ElementType Pop(ArrayStack* Stack);
ElementType Top(ArrayStack* Stack);

extern long long GetStackCount(ArrayStack* Stack); 
int IsEmpty(ArrayStack* Stack);
long long IsFull(ArrayStack* Stack);