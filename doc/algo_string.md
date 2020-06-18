String algorithms
=============

## String matching

This namespace  (`algo::strings`) contains two algorithms for string matching, the (1) Boyer Moore- and (2) Rabin Karp algorithms.

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

## Levenshtein distance

>In information theory, linguistics and computer science, the Levenshtein distance is a string metric for measuring the difference 
>between two sequences. Informally, the Levenshtein distance between two words is the minimum number of single-character edits 
>(insertions, deletions or substitutions) required to change one word into the other. [Wikipedia](https://en.wikipedia.org/wiki/Levenshtein_distance)

```c++
int LevDistance(const std::string &word_a, const std::string &word_b);
```
Returns the Levenshtein distance between the input strings `word_a` and `word_b`.

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