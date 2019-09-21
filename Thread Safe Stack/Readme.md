# Thread safe Stack (LIFO)

- Use a data structure of your choice to represent a stack of **integers**. (Linked list or dynamically allocated array). This document will consider you are using a linked list.
- One can push or pop an integer from the stack. Thus you would need two functions to accomplish these:
  - voidPush(intvalue): This function adds an integer to the Stack (linked list or array)
  - intPop(): This function removes the last element from the Stack and returns it through the function
  - The push and pop can happen simultaneously
- Another function that you need to implement is int GetStackCount(). This function returns the number of elements currently in the stack.

## Implementation

**Given**
You have been given the following files

- GetNumbers.c
- Numbers.txt
- stackHw.h (header file)

**Numbers.txt**

This is the input file **required in the same directory**. This file is used to specify numbers to push into the stack. The structure is as follows: First line indicates the size (# of values) to push. The second line specifies the numbers. The code to read this file is already given in GetNumbers.c

**GetNumbers.c**

This provides functionality to read a file specified in the above format and creates a numbers array (dynamically allocated) based on the size. This is pretty straightforward. Do not change anything in this file.

You will use the values in this array to insert into your stack.

## Functionality

Once you are able to create a stack data structure, you will implement functionality to push all the numbers that you read (using the code given) into the stack and also pop all the numbers out.

**Serial implementation**

Push all the numbers n times. Example – You read the numbers array, have a for loop that pushes everything to the stack n times

Pop all the numbers. Example – Use a for/while loop to pop all the numbers. You need to keep a count see hint below.

**Parallel implementation**

Push all the numbers n times but by dividing the pushes among threads.

Pop everything from the stack using threads – can divide the pops. The push and pop actions should not wait for each other. A thread should be able to push while other is popping/pushing. This is an important functionality to handle.

**HINT:** There will always be n x m pushes and n x m pops. Where n is the number of times you loop and m is the size of the numbers array that you read from the input. For parallel implementation, you do not need to wait for all n x m pushes to complete to start doing the pops (be time efficient).
