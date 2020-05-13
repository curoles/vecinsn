C++ SIMD Vector types and operations
====================================

This C++ header-only library provides definitions for most common
vector types and inline functions to operate on those types.
This library relies on
[GCC Vector Extentions](https://gcc.gnu.org/onlinedocs/gcc/Vector-Extensions.html)
and architecture specific intrinsics header files,
like `immintrin.h` from Intel.

See Doxygen generated API documentation
at https://github.com/curoles/vecinsn/blob/master/README.pdf

To use this _Library_ include file `vecinsn.hpp` into one of your C++ files.
Note that some inlined functions from `immintrin.h` and files it includes
require compiler flags to enable SIMD instructions, use at least `-msse4.1`.

**Attention**
> Code compiled with options to enable support for vector instructions,
> for example, `-mavx` or `-msse4.1`, will **NOT** run on a machine with CPU
> that does not support that vector instructions used to generate the program,
> even if it is the machine where the program was compiled. 

All _Library_ types and functions belong to C++ namespace `vx::`.

There are 2 naming conventions for vector types:

1. `<base-type>x<size>`, example `U32x4`
2. `V<size><base-type>`, example `V4ui`

| `C/C++ type` | mnemonic 1 | mnemonic 2 |
| :----------- | :--------: | :--------: |
| `int8_t`     | I8         | sb         |
| `uint8_t`    | U8         | ub         |
| `int16_t`    | I16        | sh         |
| `uint16_t`   | U16        | uh         |
| `int32_t`    | I32        | si         |
| `uint32_t`   | U32        | ui         |
| `int64_t`    | I64        | sl         |
| `uint64_t`   | U64        | ul         |
| `int128_t`   | I128       | sq         |
| `uint128_t`  | U128       | uq         |
| `float`      | F          | f          |
| `double`     | D          | d          |

Creating and initializing Vector type variable:

```c++
U32x4 a = {1,2,3,4};
```

Test that 2 vectors have the same elements:

```c++
V4si a = {1,2,3,4};
V4si b = {1,2,3,4};
assert(equal(a, b));
```

Compile-time function `nrelem` to get number of elements:

```c++
static_assert(nrelem<U32x2>() == 2 and sizeof(U32x2) ==  8);
static_assert(nrelem<U32x4>() == 4 and sizeof(U32x4) == 16);
static_assert(nrelem<U32x8>() == 8 and sizeof(U32x8) == 32);
static_assert(nrelem<U64x8>() == 8 and sizeof(U64x8) == 64);
```

Metaprogramming facility to dynamically construct Vector type in compile-time.
```c++
vx::make<float,8>::type dyno;
static_assert(std::is_same<vx::Fx8, decltype(dyno)>::value);
```

The _Library_ types can be used with a subset of normal C operations
that is supported by GCC. Currently, GCC allows using the following
operators on these types: `+, -, *, /, unary minus, ^, |, &, ~, %`.

```c++
V4si a = {1,2,3,4};
V4si b = {1,2,3,4};
assert(equal(a - b, (V4si){0,0,0,0}));
assert(equal(a + b + b, a * 3));
assert(equal((a + b)/2, a));
assert(equal(a % 2, (V4si){1,0,1,0}));
assert(equal(-a, (V4si){-1,-2,-3,-4}));
assert(equal(a + 1, (V4si){2,3,4,5}));
assert(equal(~a, (V4si){~1,~2,~3,~4}));
assert(equal(a | b, a));
assert(equal(a & b, a));
assert(equal(a << 1, (V4si){1<<1,2<<1,3<<1,4<<1}));
assert(equal(a << b, (V4si){1<<1,2<<2,3<<3,4<<4}));
```

Shuffle elements of one vector:
```c++
Fx4 a = {1.1, 2.2, 3.3, 4.4};
U32x4 mask = {3, 2, 1, 0}; // reverse order
assert(equal(shuffle(a, mask),(Fx4){4.4, 3.3, 2.2, 1.1}));
```

Shuffle elements of two vectors into one:
```c++
Fx4 b = {5.5, 6.6, 7.7, 8.8};
U32x4 mask2 = {3, 5, 6, 0}; // 1st 4 from a, 2nd 4 from b
assert(equal(shuffle(a, b, mask2),(Fx4){4.4, 6.6, 7.7, 1.1}));
```

Set all elements to the same value.
```c++
U32x4 a;
vx::fill(a, 7u);
assert(equal(a, (U32x4){7,7,7,7}));
a[2] = 8; // set single element value
assert(equal(a, (U32x4){7,7,8,7}));
```

Load vector from memory with `vx::load` and
store vector to memory with `vx::store`.
```c++
Fx4 va;
float a[4] = {1.1,2.2,3.3,4.4};
vx::load(va, a);
assert(equal(va, (Fx4){1.1,2.2,3.3,4.4}));
a[1] = 22.22;
std::memcpy(&va, a, sizeof va); // memcpy also works
assert(equal(va, (Fx4){1.1,22.22,3.3,4.4}));
va[2] = 33.33;
vx::store(a, va);
assert(a[2] == va[2]);
```
