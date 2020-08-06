String algorithms
=============

## String matching

This namespace  (`algo::string`) contains two algorithms for string matching, the (1) Boyer Moore- and (2) Rabin Karp algorithms.

```c++
std::vector<int> SearchBoyerMoore(std::string &text, const std::string &pattern);

std::vector<int> SearchRabinKarpSingle(const std::string &text, const std::string &pattern);
```
Return the starting positions of the string `pattern` in `text`. 

```c++
std::vector<int> SearchRabinKarpMulti(const std::string &text, std::set<std::string> patterns, int m);
```
Returns the starting positions of the strings in `patterns` in `text`. This function can search for multiple patterns in the text input.
The annoying limitation of this function is that the strings in `patterns` must be of length `m`. It is perhaps better to
implement a separate function that calls `SearchBoyerMoore` or `SearchRabinKarpSingle` with different patterns to search for.

## Longest common substring

```c++
std::string LongestCommonSubstring(std::string A, std::string B);
```

Returns the longest common substring of `A` and `B`.

For example, the longest common substrings of `abcdcucumberyupd` and `hcucumberklkk` is `cucumber`.

## String permutations

```c++
std::vector<std::string> GenerateAllPermutations(std::string &str);
```

Returns all permutations of `str`.

For example, all permutations of the input string `ABC` are the following

```text
ABC
ACB
BAC
BCA
CBA
CAB
```

Note that the number of possible permutations is equal to ![e](https://private.codecogs.com/gif.latex?n%21), where 
![e](https://private.codecogs.com/gif.latex?n%) is the string length. If the length is 10 then the number of possible permutations is
![e](https://private.codecogs.com/gif.latex?10%21%20%3D%203628800), which means that a lot of memory and execution time may be needed.

## String rotation
```c++
bool IsRotated(const std::string &str1, const std::string &str2);
```
Returns true if the input string `str2` is a rotation of `str1`.  For example `bercucum` is a rotation of `cucumber` and
`conutco` is a rotation of `coconut`.

## Simple string compression
```c++
std::string Compress(const std::string &str);
```
Returns a compressed version of `str`. For example `caaaaaaaaateeeeeepiillllar` will be compressed to `ca9te6pi2l4ar`.

## Uniqueness
```c++
bool HasUniqueChars(const std::string &str);
```
Returns true if `str` has all unique chars.

## String metrics

String metrics are usually used to compare the similarity of two strings. "How different are two strings?"
is a questions that gets answered.

### Levenshtein distance

>In information theory, linguistics and computer science, the Levenshtein distance is a string metric for measuring the difference 
>between two sequences. Informally, the Levenshtein distance between two words is the minimum number of single-character edits 
>(insertions, deletions or substitutions) required to change one word into the other. [Wikipedia](https://en.wikipedia.org/wiki/Levenshtein_distance)

```c++
int Levenshtein(const std::string &word_a, const std::string &word_b);
```
Returns the Levenshtein distance between the input strings `word_a` and `word_b`.

### Hamming distance
The hamming distance computes how many characters that are not equal, at the same position, in the 
input strings. That means that the algorithm only works on strings of equal lengths.

```c++
int Hamming(const std::string &word_a, const std::string &word_b);
```
Returns the number of different characters in `word_a` and `word_b`. 

#### Example
The hamming distance of `dude` and `dudes` is `-1` since they are not equal in length.

The hamming distance of `dude` and `rude` is `1`.

### Dice's coefficient
This algorithm computes the similarity by comparing the bigrams in the input strings. A bigram
is two consecutive characters in a string.

[Here](http://www.algomation.com/algorithm/sorensen-dice-string-similarity) is a very good demonstration 
of how the algorithm works.

```c++
double Dice(const std::string &word_a, const std::string &word_b);
```
Returns the coefficient.

The similarity is computed with

![eq](https://latex.codecogs.com/gif.latex?s%20%3D%20%5Cfrac%7B2%20n_t%7D%7Bn_a%20&plus;%20n_b%7D)

where ![eq](https://latex.codecogs.com/gif.latex?%5Csmall%20n_t) is the number of equal bigrams in 
`word_a` and `word_b`, ![eq](https://latex.codecogs.com/gif.latex?%5Csmall%20n_a) and 
![eq](https://latex.codecogs.com/gif.latex?%5Csmall%20n_b) the number of bigrams in `word_a` and `word_b`
respectively.

### Jaro-Winkler distance
The Jaro-Winkler is not a metric in a mathematical sence, since it doesn't obey the triangle inequality. Let's cheat a 
little and place the algorithm in the metric namcespace anyway together with metric algorithms. It computes
an edit ditance similar to the Levenshtein algorithm. Jaro-Winkler is ranged from 0 to 1. It favours ratings to strings 
that match from the beginning.

```c++
double JaroWinkler(const std::string &word_a, const std::string &word_b);
``` 
Returns the Jari-Winkler edit distance. For equl strings, `1.0` is returned, non-equal, `0.0`.

See the [Wikipedia](https://en.wikipedia.org/wiki/Jaro–Winkler_distance) and [GeeksforGeeks](https://www.geeksforgeeks.org/jaro-and-jaro-winkler-similarity/) 
pages on Jaro-Winkler for more information. Both links cover the mathematical theory behind the algorithm.
