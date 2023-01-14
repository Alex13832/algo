Search algorithms
===========

## Binary search
A fast search algorithm, if the input is sorted. Well, it only works for sorted input.

```c++
int Binary(const std::vector<T> &vec, const T &value);
```
If `value` is found in `vec` then the first position of `value` is returned. If not found, `-1` is returned.

## Selection min search

```c++
std::vector<T> SelectionMin(std::vector<T> vec, const T &k);
```
Returns the `k` smallest values in `vec`.  For example, `SelectionMin` would return `[1,2,3]` if `vec = [1,2,3,4,5,6,7]` and `k = 3`.

## Selection max search

```c++
std::vector<T> SelectionMax(std::vector<T> vec, const T &k);
```
Returns the `k` largest values in `vec`.  For example, `SelectionMax` would return `[5,6,7]` if `vec = [1,2,3,4,5,6,7]` and `k = 3`.