/**
 * @brief C++ Header Library of Vector Types and Operations.
 * @author Igor Lesik 2020
 * @copyright Igor Lesik 2020
 *
 * https://gcc.gnu.org/onlinedocs/gcc/Vector-Extensions.html
 * https://www.agner.org/optimize/vectorclass.pdf
 */
#pragma once

#include <cstdint>
#include <immintrin.h>

namespace vx {

#define VX_DECL(elcount, type)  __attribute__ ((vector_size (elcount*sizeof(type))))

typedef uint8_t  U8x16  VX_DECL(16, uint8_t);
typedef U8x16    V16ub;

using I8x16 = int8_t VX_DECL(16, int8_t);
using V16sb = I8x16;

typedef int32_t  I32x4  VX_DECL(4, int32_t);
typedef I32x4    V4si;

typedef uint32_t U32x4  VX_DECL(4, uint32_t);
typedef U32x4    V4ui;

typedef uint32_t U32x8  VX_DECL(8, uint32_t);
typedef U32x8    V8ui;

using U32x16 = uint32_t VX_DECL(16, uint32_t);
using V16ui = U32x16;

using U64x2 = uint64_t VX_DECL(2, uint64_t);
using V2ul = U64x2;

typedef uint64_t U64x4  __attribute__ ((vector_size (32)));
typedef U64x4    V4ul;

typedef uint64_t U64x8  __attribute__ ((vector_size (64)));
typedef U64x8    V8ul;

typedef uint32_t U32x2  __attribute__ ((vector_size (8)));
typedef U32x2    V2ui;

using Fx4 = float  VX_DECL(4, float);
using V4f = Fx4;

using Fx8 = float  VX_DECL(8, float);
using V8f = Fx8;

using Fx16 = float VX_DECL(16, float);
using V16f = Fx16;

using Dx4 = double VX_DECL(4, double);
using V4d = Dx4;

using Dx8 = double VX_DECL(8, double);
using V8d = Dx8;

union Vec128 {
    __m128i mm;
    U8x16   u8;  I8x16  i8;
    U32x4   u32; I32x4  i32;
};

template <typename T> constexpr T false_vec() { return (T){0}; }
template <typename T> constexpr T true_vec() { return !false_vec<T>(); }

/// Compare two vectors for equality.
/// @return true if all elements of two vectors are equal
template <typename T> bool equal(T a, T b)
{
    T cmp = (a == b);

    if constexpr (sizeof(T) == 32) {
        unsigned bitmask = _mm256_movemask_epi8((__m256i)cmp);
        return (bitmask == 0xffff'ffffU);
    }
    else if constexpr (sizeof(T) == 16) {
        unsigned bitmask = _mm_movemask_epi8((__m128i)cmp);
        return (bitmask == 0xffffU);
    }
    else if constexpr (sizeof(T) == 8) {
        return (uint64_t)cmp == 0xffff'ffff'ffff'ffffUL;
    }
}

#define VX_BASE_TYPE(T) decltype(((T){})[0])

/// Compile-time function that return number of elements.
///
/// static_assert(nrelem<U32x8>() == 8 and sizeof(U32x8) == 32);
///
template <typename T> constexpr unsigned nrelem()
{
    return sizeof(T)/sizeof(VX_BASE_TYPE(T));
}

/// Returns sum of all elements.
///
/// ```
/// V4ui a = {1,2,3,4};
/// assert(sum<uint32_t>(a) == (1+2+3+4));
/// ```
template <typename Acc, typename T> Acc sum(T v)
{
    if constexpr(nrelem<T>() == 8) {
        return (Acc)v[0] + v[1] + v[2] + v[3] + v[4] + v[5] + v[6] + v[7];
    }
    else if constexpr(nrelem<T>() == 4) {
        return (Acc)v[0] + v[1] + v[2] + v[3];
    }
    else if constexpr(nrelem<T>() == 2) {
        return (Acc)v[0] + v[1];
    }
}

/// @return vector {cond[0]? a[0]:b[0], cond[1] ? a[1]:b[1],...}
///
template <typename T> T select(T cond, T a, T b)
{
    return cond ? a:b;
}

///    Fx4 a = {1.1, 2.2, 3.3, 4.4};
///    U32x4 mask = {3, 2, 1, 0};
///    assert(equal(shuffle(a, mask),(Fx4){4.4, 3.3, 2.2, 1.1}));
///
template <typename T, typename M> T shuffle(T a, M mask)
{
    return __builtin_shuffle(a, mask);
}

template <typename T, typename M> T shuffle(T a, T b, M mask)
{
    return __builtin_shuffle(a, b, mask);
}

#if __GNUC__ > 8
template <typename TTo, typename TFrom> TTo convert(TFrom a)
{
    return __builtin_convertvector(a, TTo);
}
#endif

// https://www.codeproject.com/Articles/874396/Crunching-Numbers-with-AVX-and-AVX
//if AVX
//static inline __m128i int128_fill_zero() {return _mm_setzero_si128(); }
//static inline __m256i int256_fill_zero() {return _mm256_setzero_si256(); }
//endif

static inline void fill_zero(__m128i& v) {v = _mm_setzero_si128();}
static inline void fill_zero(__m256i& v) {v = _mm256_setzero_si256();}
static inline void fill_zero(__m512i& v) {v = _mm512_setzero_si512();}

static inline void fill_zero(U32x4& v) {fill_zero((__m128i&)v);}
static inline void fill_zero(U32x8& v) {fill_zero((__m256i&)v);}
static inline void fill_zero(U32x16& v) {fill_zero((__m512i&)v);}

static inline void fill_zero(U64x2& v) {fill_zero((__m128i&)v);}
static inline void fill_zero(U64x4& v) {fill_zero((__m256i&)v);}
static inline void fill_zero(U64x8& v) {fill_zero((__m512i&)v);}

static inline void fill_zero(Fx4& v) {v = _mm_setzero_ps();}
static inline void fill_zero(Fx8& v) {v = _mm256_setzero_ps();}
static inline void fill_zero(Dx4& v) {v = _mm256_setzero_pd();}
static inline void fill_zero(Dx8& v) {v = _mm512_setzero_pd();}

static inline void fill(Fx4& v, float n) {v = _mm_set1_ps(n);}
static inline void fill(Fx8& v, float n) {v = _mm256_set1_ps(n);}
static inline void fill(Dx4& v, double n) {v = _mm256_set1_pd(n);}
static inline void fill(Dx8& v, double n) {v = _mm512_set1_pd(n);}

static inline void load(Fx4& v, const float* mem) {v = _mm_load_ps(mem);}
static inline void load(Fx8& v, const float* mem) {v = _mm256_load_ps(mem);}
static inline void load(Fx16& v, const float* mem) {v = _mm512_load_ps(mem);}

static inline I8x16 add_saturated(I8x16 a, I8x16 b) {
    __m128i va = ((Vec128){i8:a}).mm;
    __m128i vb = ((Vec128){i8:b}).mm;
    return ((Vec128){mm:_mm_adds_epi8(va, vb)}).i8;
}

static inline Fx4 madd(Fx4 a, Fx4 b, Fx4 c) {return _mm_fmadd_ps(a, b, c);}

} // namespace vx
