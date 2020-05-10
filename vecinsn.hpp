/**
 * @brief C++ Header Library of Vector Types and Operations.
 * @author Igor Lesik 2020
 * @copyright Igor Lesik 2020
 *
 * https://gcc.gnu.org/onlinedocs/gcc/Vector-Extensions.html
 * https://software.intel.com/sites/landingpage/IntrinsicsGuide
 */
#pragma once

#include <cstdint>
#include <immintrin.h>

namespace vx {

using uint128_t = __uint128_t;
using  int128_t =  __int128_t;

#define VX_DECL(elcount, type)  __attribute__ ((vector_size (elcount*sizeof(type))))

#define VX_DEF(type,mn,mn2,count) \
using mn##x##count = type VX_DECL(count, type); \
using V##count##mn2 = mn##x##count;

#define VX_DEF2(type,mn,mn2) VX_DEF(type,mn,mn2,2)
#define VX_DEF4(type,mn,mn2) VX_DEF(type,mn,mn2,4) VX_DEF2(type,mn,mn2)
#define VX_DEF8(type,mn,mn2) VX_DEF(type,mn,mn2,8) VX_DEF4(type,mn,mn2)
#define VX_DEF16(type,mn,mn2) VX_DEF(type,mn,mn2,16) VX_DEF8(type,mn,mn2)
#define VX_DEF32(type,mn,mn2) VX_DEF(type,mn,mn2,32) VX_DEF16(type,mn,mn2)
#define VX_DEF64(type,mn,mn2) VX_DEF(type,mn,mn2,64) VX_DEF32(type,mn,mn2)

VX_DEF64( uint8_t, U8,ub)
VX_DEF64(  int8_t, I8,sb)
VX_DEF32(uint16_t,U16,uh)
VX_DEF32( int16_t,I16,sh)
VX_DEF16(uint32_t,U32,ui)
VX_DEF16( int32_t,I32,si)
VX_DEF8 (uint64_t,U64,ul)
VX_DEF8 ( int64_t,I64,sl)
VX_DEF4 (uint128_t,U128,uq)
VX_DEF4 ( int128_t,I128,sq)

VX_DEF16( float,F,f)
VX_DEF8 (double,D,d)

union Vec64 {
    __m64 mm;
    U8x8     u8; I8x8   i8;
    U16x4   u16; I16x4  i16;
    U32x2   u32; I32x2  i32;
    uint64_t   u64; int64_t  i64;
};

union Vec128 {
    __m128i mm;
    U8x16    u8; I8x16   i8;
    U16x8   u16; I16x8  i16;
    U32x4   u32; I32x4  i32;
    U64x2   u64; I64x2  i64;
    uint128_t u128; int128_t  i128;
};

union Vec256 {
    __m256i mm;
    U8x32    u8; I8x32    i8;
    U16x16  u16; I16x16  i16;
    U32x8   u32; I32x8   i32;
    U64x4   u64; I64x4   i64;
    U128x2 u128; I128x2 i128;
};

union Vec512 {
    __m512i mm;
    U8x64    u8; I8x64    i8;
    U16x32  u16; I16x32  i16;
    U32x16  u32; I32x16  i32;
    U64x8   u64; I64x8   i64;
    U128x4 u128; I128x4 i128;
};

/// Returns 'false' vector {0,0,0,...}
template <typename T> constexpr T false_vec() { return (T){0}; }

/// Returns 'true' vector {-1,-1,-1,...}
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

/// Compile-time function that returns number of elements.
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

static inline int test_all_ones(U64x2 v) {return _mm_test_all_ones((__m128i)v);}
static inline int test_all_ones(I64x2 v) {return _mm_test_all_ones((__m128i)v);}
static inline int test_all_ones(U32x4 v)  {return _mm_test_all_ones((__m128i)v);}
static inline int test_all_ones(I32x4 v) {return _mm_test_all_ones((__m128i)v);}
static inline int test_all_ones(U16x8 v) {return _mm_test_all_ones((__m128i)v);}
static inline int test_all_ones(I16x8 v) {return _mm_test_all_ones((__m128i)v);}
static inline int test_all_ones(U8x16 v) {return _mm_test_all_ones((__m128i)v);}
static inline int test_all_ones(I8x16 v) {return _mm_test_all_ones((__m128i)v);}
static inline int test_all_ones(Fx4   v) {return _mm_test_all_ones((__m128i)v);}
static inline int test_all_ones(Dx2   v) {return _mm_test_all_ones((__m128i)v);}

static inline int test_all_zeros(U64x2 v, uint128_t m = -1) {return _mm_test_all_zeros((__m128i)v, (__m128i)m);}
static inline int test_all_zeros(I64x2 v, uint128_t m = -1) {return _mm_test_all_zeros((__m128i)v, (__m128i)m);}
static inline int test_all_zeros(U32x4 v, uint128_t m = -1) {return _mm_test_all_zeros((__m128i)v, (__m128i)m);}
static inline int test_all_zeros(I32x4 v, uint128_t m = -1) {return _mm_test_all_zeros((__m128i)v, (__m128i)m);}
static inline int test_all_zeros(U16x8 v, uint128_t m = -1) {return _mm_test_all_zeros((__m128i)v, (__m128i)m);}
static inline int test_all_zeros(I16x8 v, uint128_t m = -1) {return _mm_test_all_zeros((__m128i)v, (__m128i)m);}
static inline int test_all_zeros(U8x16 v, uint128_t m = -1) {return _mm_test_all_zeros((__m128i)v, (__m128i)m);}
static inline int test_all_zeros(I8x16 v, uint128_t m = -1) {return _mm_test_all_zeros((__m128i)v, (__m128i)m);}
static inline int test_all_zeros(Fx4   v, uint128_t m = -1) {return _mm_test_all_zeros((__m128i)v, (__m128i)m);}
static inline int test_all_zeros(Dx2   v, uint128_t m = -1) {return _mm_test_all_zeros((__m128i)v, (__m128i)m);}

static inline void fill_zero(__m64&   v) {v = _mm_setzero_si64();}
static inline void fill_zero(__m128i& v) {v = _mm_setzero_si128();}
static inline void fill_zero(__m256i& v) {v = _mm256_setzero_si256();}
static inline void fill_zero(__m512i& v) {v = _mm512_setzero_si512();}

static inline void fill_zero(U32x2& v)  {fill_zero((__m64  &)v);}
static inline void fill_zero(U32x4& v)  {fill_zero((__m128i&)v);}
static inline void fill_zero(U32x8& v)  {fill_zero((__m256i&)v);}
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

static inline void fill(U32x4& v, uint32_t n) {v = (U32x4)_mm_set1_epi32(n);}

static inline void load(Fx4& v, const float* mem) {v = _mm_load_ps(mem);}
static inline void load(Fx8& v, const float* mem) {v = _mm256_load_ps(mem);}
static inline void load(Fx16& v, const float* mem) {v = _mm512_load_ps(mem);}

static inline I8x16 add_saturated(I8x16 a, I8x16 b) {
    return (I8x16)_mm_adds_epi8((__m128i)a, (__m128i)b);
}

static inline Fx4 madd(Fx4 a, Fx4 b, Fx4 c) {return _mm_fmadd_ps(a, b, c);}

} // namespace vx
