Bit algorithms
==================

### Legend
```C++
&     And
^     Exclusive or
|     or
~     not (exclude)
```

### Algorithms
Tested in C

#### The sign of an integer `x`
```C
-(x < 0)
```

#### The sign of an integer `x`, economy

This saves one operation
```C
x >> (sizeof(int) * CHAR_BIT - 1)
```

#### Test if `x` is even
```C
(x & 1) == 0
```

#### Test if bit `n` in `x` is 1
```C
(x & (1 << n))
```

#### Set bit `n` in `x`to 1
```C
(x | (1 << n))
```

#### Set bit `n`in `x`to 0
```C
(x & ~(1 << n))
```

#### Flip bit `n` `x` to the opposite bit value
```C
(x ^ (1 << n))
```

#### Calculate the absolute value of the integer `x`
```C
int const mask = x >> (sizeof(int) * CHAR_BIT - 1)
unsigned abs = (x + mask) ^ mask;
```

#### Find the smallest of `x` and `y`
```C
x < y ? x : y
```

#### Find the smallest of `x`, `y` and `z`
```C
x < y ? (x < z ? x : z) : (y < z ? y : z)
```


#### Find the maximum of `x` and `y`
```C
x > y ? x : y
```

#### Find if `x` is a power of 2
```C
x && !(x & (x - 1))
```

#### Find the next power of 2 after `x`
```C
unsigned count = 0;

if (x && !(x & (x -  1)))
    return x;

while (x != 0) {
    x >>= 1;
    count++;
}

unsigned next_pow_2 = 1 << count;
```

#### Swap the bits in `x`
```C
unsigned int n = next_power_of2(x);
int swapped = x ^ (n - 1);
```

#### Count the set bits in `x`
```C
n == 0 ? 0 : ((n % 2 == 0 ? 0 : 1) + count_bits(n/2))
```

#### Adds two numbers `x` and `y` with bit operations
```C
while (y != 0) {
    int carry = x & y;
    x = x ^ y;
    y = carry << 1;
}

int sum = x;
```

### Modulo operation, only for divisors `n` that are powers of two
```C
(x & (n - 1))
```