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