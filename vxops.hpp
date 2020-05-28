/**@file
 * @brief     Operations on Vector Types.
 * @author    Igor Lesik 2020
 * @copyright Igor Lesik 2020
 *
 *
 * This code relies on
 * [GCC Vector Extentions](https://gcc.gnu.org/onlinedocs/gcc/Vector-Extensions.html)
 * and architecture specific intrinsics header files,
 * like `immintrin.h` from Intel.
 *
 *
 * References:
 * - https://gcc.gnu.org/onlinedocs/gcc/Vector-Extensions.html
 * - https://software.intel.com/sites/landingpage/IntrinsicsGuide
 *
 */
#pragma once

#include "vxtypes.hpp"

/// Namespace of all vector types and functions.
///
namespace vx {

/// Test all bits of all elements are 1.
static inline int test_all_ones(U64x2 v) {return _mm_test_all_ones((__m128i)v);}
static inline int test_all_ones(I64x2 v) {return _mm_test_all_ones((__m128i)v);}
static inline int test_all_ones(U32x4 v) {return _mm_test_all_ones((__m128i)v);}
static inline int test_all_ones(I32x4 v) {return _mm_test_all_ones((__m128i)v);}
static inline int test_all_ones(U16x8 v) {return _mm_test_all_ones((__m128i)v);}
static inline int test_all_ones(I16x8 v) {return _mm_test_all_ones((__m128i)v);}
static inline int test_all_ones(U8x16 v) {return _mm_test_all_ones((__m128i)v);}
static inline int test_all_ones(I8x16 v) {return _mm_test_all_ones((__m128i)v);}
static inline int test_all_ones(Fx4   v) {return _mm_test_all_ones((__m128i)v);}
static inline int test_all_ones(Dx2   v) {return _mm_test_all_ones((__m128i)v);}

/// Test all bits of all elements are 0.
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

/// Set all bits of all elements to 0.
static inline void fill_zero(U32x4& v)  {fill_zero((__m128i&)v);}
static inline void fill_zero(U32x2& v)  {fill_zero((__m64  &)v);}
static inline void fill_zero(U32x8& v)  {fill_zero((__m256i&)v);}
static inline void fill_zero(U32x16& v) {fill_zero((__m512i&)v);}

static inline void fill_zero(U64x2& v) {fill_zero((__m128i&)v);}
static inline void fill_zero(U64x4& v) {fill_zero((__m256i&)v);}
static inline void fill_zero(U64x8& v) {fill_zero((__m512i&)v);}

static inline void fill_zero(Fx4& v) {v = _mm_setzero_ps();}
static inline void fill_zero(Fx8& v) {v = _mm256_setzero_ps();}
static inline void fill_zero(Dx4& v) {v = _mm256_setzero_pd();}
static inline void fill_zero(Dx8& v) {v = _mm512_setzero_pd();}

/// Set a single value to all elements.
static inline void fill(Fx4& v, float n) {v = _mm_set1_ps(n);}
static inline void fill(Fx8& v, float n) {v = _mm256_set1_ps(n);}
static inline void fill(Dx4& v, double n) {v = _mm256_set1_pd(n);}
static inline void fill(Dx8& v, double n) {v = _mm512_set1_pd(n);}

static inline void fill(U32x4& v, uint32_t n) {v = (U32x4)_mm_set1_epi32(n);}

/// Load vector from memory.
static inline void load(Fx4& v, const float* mem) {v = _mm_load_ps(mem);}
static inline void load(Fx8& v, const float* mem) {v = _mm256_load_ps(mem);}
static inline void load(Fx16& v, const float* mem) {v = _mm512_load_ps(mem);}

/// Store vector to memory.
static inline void store(float* mem, Fx4 v) {_mm_store_ps(mem, v);}


static inline I8x8  add(I8x8  a, I8x8  b) {return (I8x8) _mm_add_pi8 ((__m64)a, (__m64)b);}
static inline I16x4 add(I16x4 a, I16x4 b) {return (I16x4)_mm_add_pi16((__m64)a, (__m64)b);}
static inline I32x2 add(I32x2 a, I32x2 b) {return (I32x2)_mm_add_pi32((__m64)a, (__m64)b);}
static inline I64x2 add(const I64x2 a, const I64x2 b) {return (I64x2)_mm_add_epi64((__m128i)a, (__m128i)b);}
static inline Dx2   add(const Dx2 a, const Dx2 b) {return (Dx2)_mm_add_pd((__m128d)a, (__m128d)b);}

static inline I8x8  sub(I8x8  a, I8x8  b) {return (I8x8) _mm_sub_pi8 ((__m64)a, (__m64)b);}
static inline I16x4 sub(I16x4 a, I16x4 b) {return (I16x4)_mm_sub_pi16((__m64)a, (__m64)b);}
static inline I32x2 sub(I32x2 a, I32x2 b) {return (I32x2)_mm_sub_pi32((__m64)a, (__m64)b);}
static inline Dx2   sub(const Dx2 a, const Dx2 b) {return (Dx2)_mm_sub_pd((__m128d)a, (__m128d)b);}

static inline I8x8  add_saturated(I8x8  a, I8x8  b) {return (I8x8)_mm_adds_pi8((__m64)a, (__m64)b);}
static inline U8x8  add_saturated(U8x8  a, U8x8  b) {return (U8x8)_mm_adds_pu8((__m64)a, (__m64)b);}
static inline I16x4 add_saturated(I16x4 a, I16x4 b) {return (I16x4)_mm_adds_pi16((__m64)a, (__m64)b);}
static inline U16x4 add_saturated(U16x4 a, U16x4 b) {return (U16x4)_mm_adds_pu16((__m64)a, (__m64)b);}

static inline I8x16 add_saturated(I8x16 a, I8x16 b) {return (I8x16)_mm_adds_epi8((__m128i)a, (__m128i)b);}


static inline Dx2 mul(const Dx2 a, const Dx2 b) {return (Dx2)_mm_mul_pd((__m128d)a, (__m128d)b);}
#ifdef __AVX__
static inline Dx4 mul(const Dx4 a, const Dx4 b) {return (Dx4)_mm256_mul_pd((__m256d)a, (__m256d)b);}
#endif

static inline Fx4 madd(Fx4 a, Fx4 b, Fx4 c) {return _mm_fmadd_ps(a, b, c);}



} // namespace vx
