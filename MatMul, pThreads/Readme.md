# Part 1

Your task is to optimize matrix multiplication (matmul) code to run fast(er) on a single processor core of Ulabany’s RIT cluster.

We consider a special case of matmul:

C := C + A\*B

where A, B, and C are n x n matrices. This can be performed using 2n<sup>3</sup> floating point operations (n<sup>3</sup> adds, n<sup>3</sup> multiplies), as in the following pseudocode:

```
for i = 1 to n
    for j = 1 to n
        for k = 1 to n
            C(i,j) = C(i,j) + A(i,k) * B(k,j)
        end
    end
end
```

# Part 2

In this part you will learn how threading helps speed up computations by leveraging multicore systems. You will use pThreads.

You will do a serial and a parallel implementation and show the speedup.

Write the following programs in C

## Serial Program

- Write a function void SumUpto(int number). This function sums all the numbers from 0 to “number” and prints the sum on stdout
- Call this function from main. The value for “number” should be passed in as a command line parameter.
- Once this works, enclose the function call in a for loop (0 to p)
  - The for loop upper limit (p) parameter should be passed in as a command line parameter (if no parameter is specified, use default as 2)
- Time the execution (start of main to end of main) – time in microseconds.

## Parallel Program using pThreads

- Write the thread function void * SumUpto(void *arg). Note this is same as above. You can pass in the “number” as the thread argument (arg)
- Create threads in main using the SumUpto function
  - Use command line argument to determine how many threads (p) to create. If no argument is specified, use 2
  - The value for “number” should also be passed in as a command line parameter.

# Part 3

Given is a matrix of NxN integers (you create this). The matrix is initialized to random values between 1 and 10 inclusive. The problem is to calculate the distribution of values, i.e., the number of elements that are 1, the number that are 2, etc.

Divide the work up among P worker processes (threads). The matrix is shared by the workers.

You may NOT assume that N is a multiple of P. Divide the matrix into almost P equal-size strips of rows. Each worker will ONLY calculate the distribution of its strip(s). When all workers have completed their tasks, only one worker should accumulate and print the distributions.

Use the C rand number function with seed to generate psuedo-random numbers.

The values of N and P should be read as command-line arguments. Write the results to standard output.

Run experiments for N between 64 - 1000 and P between, 2 to 64. (NOTE: for serial code, P =1)

N and P are command line args
