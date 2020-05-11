C++ SIMD Vector types and operations
====================================

This C++ header-only library provides definitions for most common
vector types and inline functions to operate on those types.
This library relies on
[GCC Vector Extentions](https://gcc.gnu.org/onlinedocs/gcc/Vector-Extensions.html)
and architecture specific intrinsics header files,
like `immintrin.h` from Intel.

To use this library include file `vecinsn.hpp` into one of your C++ files.
Note that some inlined functions from `immintrin.h` and files it includes
require compiler flags to enable SIMD instructions, use at least `-msse4.1`.

**Attention**
> Code compiled with options to enable support for vector instructions,
> for example, `-mavx` or `-msse4.1`, will **NOT** run on a machine with CPU
> that does not support that vector instructions used to generate the program,
> even if it is the machine where the program was compiled. 

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

The _Library_ types can be used with a subset of normal C operations
that is supported by GCC. Currently, GCC allows using the following
operators on these types: `+, -, *, /, unary minus, ^, |, &, ~, %`.


