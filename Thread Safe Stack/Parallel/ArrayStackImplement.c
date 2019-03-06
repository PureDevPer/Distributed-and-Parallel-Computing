// Wooseok Kim
// Homework #3 - Parallel

#include "stackHw.h"


void CreateStack(ArrayStack** Stack, int Capacity)
{
	(*Stack) = (ArrayStack*)malloc(sizeof(ArrayStack));

	(*Stack)->Nodes = (Node*)malloc(sizeof(Node)*Capacity);

	(*Stack)->Top = 0;
	(*Stack)->Capacity = Capacity;
}

void DestroyStack(ArrayStack* Stack)
{
	free(Stack->Nodes);
	free(Stack);
}


void Push(ArrayStack* Stack, ElementType Data)
{
	int Position = Stack->Top;

	Stack->Nodes[Position].Data = Data;
	Stack->Top++;
}

ElementType Pop(ArrayStack* Stack)
{
	int Position = --(Stack->Top);
	return Stack->Nodes[Position].Data;
}


ElementType Top(ArrayStack* Stack)
{
	int Position = Stack->Top-1;
	return Stack->Nodes[Position].Data;
}

long long GetStackCount(ArrayStack* Stack)
{
	return Stack->Top;
}

int IsEmpty(ArrayStack* Stack)
{
	return (Stack->Top==0);
}

long long IsFull(ArrayStack* Stack)
{
	return ((Stack->Top) >= (Stack->Capacity));
}