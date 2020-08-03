Bit algorithms
=====================

The namespace `algo::bit` offers a set of bit manipulation algorithms. They can help when the number of 
operations is required to be low or when to avoid importing other libraries so save space. 

## The algorithms

These functions are `constexpr` lambda-functions in a header-file. Using them should allow the compiler 
to determine sizes in compile-time.  

### Check sign of an input number
```c++
constexpr auto Sign = [](const auto& x);
```
Returns `0` if x is positive otherwise `-1`.

#### Usage

```c++
int sign{algo::bit::Sign(-1)};
```

### Check if an input is even
```c++
constexpr auto IsEven = [](const auto& x);
```
Returns `true` if `x` is even, `false` if odd.

#### Usage
```c++
bool even{algo::bit::IsEven(2)};
```

### Set a specific bit
```c++
constexpr auto SetBit = [](const auto& x, const auto& n, const Bit& b);
```
Changes `x` at bit position `n` to either `0` or `1`.

#### Example
```c++
unsigned int num{algo::bit::SetBit(0xFFFFF, 15, algo::bit::Bit::False)}; // == 0xF7FFF
```

### Check if a bit is set
```c++
constexpr auto IsBit = [](const auto& x, const auto& n);
```
Returns true if bit number `n` in `x` is `1`, otherwise false.

#### Example
```c++
bool is_bit{algo::bit::IsBit(0xAAAA, 11)}; // == true
```

### Toogle a bit
```c++
constexpr auto ToggleBit = [](const auto& x, const auto& n);
```
Changes a bit at position `n` in `x`, zero to one or one to zero.

#### Example
```c++
unsigned int{algo::bit::ToggleBit(0xBBBB, 14)}; // == 0xFBBB
```

### Check if a number is a power of 2
```c++
constexpr auto IsPow2 = [](const auto& x);
```
Returns true if `x` is a power of two, e.g. ![eq](https://latex.codecogs.com/gif.latex?%5Csmall%202%5E3%20%3D%208) is a power of 2.

#### Example
```c++
bool is_pow2{algo::bit::IsPow2(1024)}; // ==  true
```
![eq](https://latex.codecogs.com/gif.latex?%5Csmall%202%5E%7B10%7D%20%3D%201024).

### Get the next power of 2
```c++
constexpr auto NextPow2 = [](auto x);
```
Returns the next power of two, e.g. the next power of two of 1025 is 2048.

#### Example
```c++
unsigned int next_pow2{algo::bit::NextPow2(1025)}; // == 2048
```

### Count number of 1s in a number
```c++
constexpr auto CountSetBits = [](auto x);
```
Returns the number of set bits, the number of 1s, in a (binary) number. 

#### Example
```c++
unsigned count{algo::bit::CountSetBits(0xFF)}; // == 8
``` 
![eq](https://latex.codecogs.com/gif.latex?%5Csmall%20%5Ctextup%7BFF%7D_%7B16%7D%20%3D%2011111111_%7B2%7D)

### Swap the bits in a number
```c++
constexpr auto SwapBits = [](const auto& x);
```
Changes all the true bits to false, and all false bit to true in the input number `x`.

#### Example
```c++
unsigned int swapped{algo::bit::SwapBits(170)}; // == 85
```