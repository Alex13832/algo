Math algorithms
==========

| Namespace | Description |
|---|---|
|`algo::math::discrete`             |Algorithms derived from discrete/combinatorial mathematics.    |
|`algo::math::random_num`           |Random numbers.                                                |
|`algo::math::random_num::cont`     |Random numbers using continuous probability distributions.     |
|`algo::math::random_num::discr`    |Random numbers using discrete probability distributions.       |
|`algo::math::prime`                |Prime numbers.                                                 |

# Discrete mathematics algorithms

## Pascal's triangle

```c++
PTriangle PascalsTriangle(const unsigned int& depth);
```
Returns the first number of rows defined by `depth` of the Pascal's triangle. `PTriangle` is the same as 
`std::vector<std::vector<int>>`. Each item at row ![e](https://private.codecogs.com/gif.latex?n) and 
column ![e](https://private.codecogs.com/gif.latex?k) is computed as the binomial coefficient

![e](https://private.codecogs.com/gif.latex?%5Clarge%20%5Cbinom%7Bn%7D%7Bk%7D%20%3D%20%5Cfrac%7Bn%21%7D%7Bk%21%28n-k%29%21%29%7D)

The first six rows in the Pascal's triangle are:

![PT](https://upload.wikimedia.org/wikipedia/commons/thumb/2/28/PascalsTriangle.png/250px-PascalsTriangle.png)

### Usage
```c++
#include <algo_math.hpp>
#include <iostream>

using namespace algo::math::discrete;
usign namespace std;

...

PTriangle rows{discrete::PascalsTriangle(5)};

for (const auto& row: rows) {
  for (const auto& k: row) {
    cout << k << " ";
  } 
  cout << endl;
}
```

Output:

```text
> 1 
> 1 1 
> 1 2 1 
> 1 3 3 1 
> 1 4 6 4 1 
> 1 5 10 10 5 1 
```

## Clock angle

```c++
int ClockAngle(const int &h, const int &m)
```
Reurns the angle between the hour and minute hands.

## Knapsack problem, resource allocation
> The knapsack problem is a problem in combinatorial optimization: Given a set of items, each with a weight and a value, 
>determine the number of each item to include in a collection so that the total weight is less than or equal to a given 
>limit and the total value is as large as possible. It derives its name from the problem faced by someone who is 
>constrained by a fixed-size knapsack and must fill it with the most valuable items. The problem often arises in resource 
>allocation where the decision makers have to choose from a set of non-divisible projects or tasks under a fixed budget 
>or time constraint, respectively. [Wikipedia](https://en.wikipedia.org/wiki/Knapsack_problem)

```c++
int Knapsack(const Items& items, unsigned capacity);
```
Returns the maximum value that is possible to put in the knapsack without overloading the maximum capacity. The `items`
hold the value and capacity for each item. `Items` is the same as `std::vector<Item>` and contains 
`Item{int value, weight}`.

### Usage

```c++
#include <algo_mathc.hpp>

using namespace algo::math::discrete;

...

// Value, weight
Items items{{60, 10},
            {100, 20},
            {120, 30}};

int max_load{Knapsack(items, 50)}; // 220
```

## The Euclidean algorithm
>In mathematics, the Euclidean algorithm, or Euclid's algorithm, is an efficient method for computing the greatest common divisor (GCD) of two integers (numbers), 
>the largest number that divides them both without a remainder. [Wikipedia](https://en.wikipedia.org/wiki/Euclidean_algorithm)

With the properties of GCD, it can be used to compute the least common divisor, LCM: 

![e](https://private.codecogs.com/gif.latex?%5Clarge%20%5Coperatorname%7Blcm%7D%28a%2Cb%29%3D%5Cfrac%7B%7Ca%5Ccdot%20b%7C%7D%7B%5Coperatorname%7Bgcd%7D%28a%2Cb%29%7D.)

The GCD and LCM functions are simple enough to be declared as constexpr lambdas:

```c++
constexpr auto GCD = [](auto a, auto b) {...};

constexpr auto LCM = [](auto a, auto b) {...};
```

## Binomial coefficients

This function is also called ![e](https://private.codecogs.com/gif.latex?n) choose ![e](https://private.codecogs.com/gif.latex?k). 
What the function is returning is the answer for the question _"how many times can I choose ![e](https://private.codecogs.com/gif.latex?k) 
different elements from a set of ![e](https://private.codecogs.com/gif.latex?n) unique elements?"_

It's calculated with

![e](https://private.codecogs.com/gif.latex?%5Clarge%20%5Cbinom%7Bn%7D%7Bk%7D%20%3D%20%5Cfrac%7Bn%21%7D%7Bk%21%28n-k%29%21%29%7D)

```c++
constexpr auto BIN = [](auto n, auto k) {...};
```
Retuns the result of ![e](https://private.codecogs.com/gif.latex?%5Csmall%20%5Cbinom%7Bn%7D%7Bk%7D).