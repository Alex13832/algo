Algo
===============================
This repository contains implementations of various known algorithms from selected fields of algorithm design in computer science, 
mathematics, data mining and etc. A not so unrealistic goal is to have the source code 100% unit tested and a 100% code coverage. 


### Constraints

The algorithms are implemented **only** using the C++ standard library.

The examples in `examples/` may use additional libraries but should not be required when building the library itself.

### Resources

#### Data
For generating and plotting data, the [Orange](https://orange.biolab.si) data mining tool is used. It's super easy to 
output a data set in csv format to play with. The result of the C++ algorithms may then be plotted with the 
same tool. Not a single line of code.

#### Unit tests
The C++ code is tested with the [Google Test](https://github.com/google/googletest) framework.

### A brief overview

#### Data mining

```C++
algo::data_mining {
  
// Returns the K-means of the input points.
Clusters KMeans(Points points, const std::int8_t& k);
};
```

#### Geometry
```C++
algo::geometry {
  
// Returns the convex hull of the input points.
Points ConvexHull(Points points);

// Returns the closest pair of points.
Points ClosestPairOfPoints(const Points& points);

// Returns the lines between the points of a triangulation.
Lines Triangulate(Points& pts);
};
```

#### Greedy

```C++
algo::greedy {
  
// Returns the stable matching between preferred choices in two sets.
std::vector<Match> StableMatching(Prefs men_pref, Prefs women_pref);
};
```

#### Math

```C++
algo::math::discrete {
  
// Returns the n rows of the Pascal's triangle.
std::vector<std::vector<int>> PascalsTriangle(const unsigned int& depth);

// Returns the angle between the hour and minute hands.
int ClockAngle(const int& h, const int& m);

// Finds the maximum value subset of v such that sum of the weights of this subset is smaller.
unsigned int Knapsack(const std::vector<int>& v, const std::vector<int>& w, unsigned capacity);

// Returns the greatest common divisor of a and b.
T Gcd(T a, T b);

// Returns the least common divisor of a and b.
T Lcm(T a, T b);

// Return sthe binomial coefficient of n and k-.
T Bin(T n, T k);
};
```

```C++
algo::math::random_num::cont {
  
// Returns a random number sampled from a uniform distribution with lower and upper limits a and b.
double Uniform(const double& a, const double& b);

// Returns a random number from the uniform distribution between 0 and 1.
double Random();

// Returns an exponentially distributed random number.
double Exp(const double& lambda);

// Returns a normal distributed random number, N(mu, sigma). The random number is computed using the Box-Muller method.
double Normal(const double& mu, const double& sigma);

// Returns a random number sampled from the Weibull distribution.
double Weibull(const double& lambda, const double& k);
};
```

```C++
algo::math::random_num::discr {
  
// Returns a random number sampled from the Binomial distribution.
int Binomial(const int& n, const double& p);

// Returns a random number sampled from the Poisson distribution.
int Poisson(const double& lambda);

// Returns a random number sampled from the geometric distribution.
int Geometric(const double& p);
};
```

```C++
algo::math::prime {
  
// Checks if n is a prime number.
bool IsPrime(T n);

// Returns prime numbers less than n in a vector. This implementation is based on the Sieve of Eratosthenes
std::vector<T> GetPrimes(unsigned int n);
};
```

#### Network

```C++
algo::network {
  
// Computes the rank for the input web graph. 
Arr PageRank(const Mat &W, const double &damping, const double &error);

// Converts a matrix with link counts to a transition matrix with probabilities.
Mat MatTransition(const Mat &M, const Arr &deg);
};
```

#### Searching

```C++
algo::search {
  
//
int Binary(const std::vector<T> &vec, const T &value);

//
std::vector<T> SelectionMin(std::vector<T> vec, const T &k);

//
std::vector<T> SelectionMax(std::vector<T> vec, const T &k);
};
```

#### Sequence

```C++
algo::sequence {
  
// Returns the longest increasing sub sequence of an input sequence.
std::vector<T> LongestIncreasingSub(const std::vector<T>& seq);

// Finds the largest sum of any continuous subarray in vec.
T MaxSubarray(const std::vector<T>& vec);
};
```

#### Sorting

```C++
algo::sort {
  
void Bubble(std::vector<T> &vec);

void Bucket(std::vector<T> &vec);

void Gnome(std::vector<T> &vec);

void Heap(std::vector<T> &vec);

void Insertion(std::vector<T> &vec);

void Merge(std::vector<T> &lst);

void Quick(std::vector<T> &vec);
};
```

#### String

```C++
algo::string {
  
// The algorithm tells whether a given text contains a substring which is "approximately equal" to a given pattern.
std::string BitapSearch(const std::string &text, const std::string &pattern);

// Returns the found locations of the pattern in text.
std::vector<int> SearchBoyerMoore(std::string &text, const std::string &pattern);

// Returns the longest common substring that exists in A and B.
std::string LongestCommonSubstring(std::string A, std::string B);

// Returns the starting positions of the substring pattern in text.
std::vector<int> SearchRabinKarpSingle(const std::string &text, const std::string &pattern);

// Returns the starting positions of the substring patterns in patterns.
std::vector<int> SearchRabinKarpMulti(const std::string &text, std::set<std::string> patterns, int m);

// Generates all permutations of the input string str using Heap's algorithm.
std::vector<std::string> GenerateAllPermutations(std::string &str);

// Calculates the Levenshtein distance between two strings. This is a string metric for measuring the
int LevDistance(const std::string &word_a, const std::string &word_b);

// Checks if str2 is a rotation of str1, e.g: atc is a rotation of cat.
bool IsRotated(const std::string &str1, const std::string &str2);

// Compresses the input string, e.g: `Compress("caaaattt") = "ca4t3"`.
std::string Compress(const std::string &str);

// Tests if the input string has unique chars. Only works fo ASCII [0...255].
bool HasUniqueChars(const std::string &str);
};
```

