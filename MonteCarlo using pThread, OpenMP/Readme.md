# The value of PI

- For the parallel version of Monte Carlo simulation, you will create two binaries
  - Part 1: One where you only use pthreads
  - Part 2: Other using only openmp
- Part 3: Convert <a href="https://github.com/PureDevPer/Distributed-and-Parallel-Computing/tree/master/MatMul%2C%20pThreads/Part3">pThread’s part 3</a> to use omp instead of pThreads

# Description

## Monte Carlo simulation

Monte Carlo methods can be thought of as statistical simulation methods that utilize a sequences of random numbers to perform the simulation. In a typical process one computes the number of points in a set A that lies inside box R. The ratio of the number of points that fall inside A to the total number of points tried is equal to the ratio of the two areas. The accuracy of the ratio p depends on the number of points used, with more points leading to a more accurate value.

## Monte Carlo simulation of PI

- Consider a circle inscribed in a unit square. Given that the circle and the square have a ratio of areas that is p = π/4, the value of π can be approximated using a Monte Carlo method
  - Draw a square on the ground, then inscribe a circle within it.
  - Uniformly scatter some objects of uniform size (grains of rice or sand) over the square.
  - Count the number of objects inside the circle and the total number of objects.
  - The ratio of the two counts is an estimate of the ratio of the two areas, which is π/4 or p. Multiply the result by 4 to estimate π.

A simple Monte Carlo simulation to approximate the value of π could involve randomly selecting points {(x<sub>i</sub>, y<sub>i</sub>)} in the unit square and determining the ratio p = m/n, where m is number of points that satisfy x<sub>i</sub><sup>2</sup> + y<sub>i</sub><sup>2</sup> <= 1.

In a typical simulation of sample size n = 1000 if there were 787 points satisfying x<sub>i</sub><sup>2</sup> + y<sub>i</sub><sup>2</sup> <= 1.

p = m / n = 787 / 1000 = 0.787 and π = p _ 4 = 0.787 _ 4 = 3.148
