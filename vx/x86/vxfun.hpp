/**@file
 * @brief     Advanced Vector operations.
 * @author    Igor Lesik 2020
 * @copyright Igor Lesik 2020
 *
 */
#pragma once

namespace vx {


/// Returns sum of all elements.
///
/// Example:
/// ```c++
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

#ifdef __AVX__
// https://stackoverflow.com/questions/49941645/get-sum-of-values-stored-in-m256d-with-sse-avx
//
template <> double sum<double,F64x4>(F64x4 v)
{
    __m128d vlow  = _mm256_castpd256_pd128(v);
    __m128d vhigh = _mm256_extractf128_pd(v, 1); // high 128
            vlow  = _mm_add_pd(vlow, vhigh);     // reduce down to 128

    __m128d high64 = _mm_unpackhi_pd(vlow, vlow);
    return  _mm_cvtsd_f64(_mm_add_sd(vlow, high64));  // reduce to scalar
}
#endif

//inner product v = sum (mul(v1,v2))
template <typename Acc, typename V>
Acc dot(const V& v1, const V& v2)
{
    V v = vx::mul(v1, v2);
    return sum<Acc,V>(v);
}

/// Change sign: a -> -a
template <typename V>
V inverse(const V& v)
{
    V zero;
    vx::fill_zero(zero);

    return vx::sub(zero, v); // 0 - a == -a
}

} //namespace vx

