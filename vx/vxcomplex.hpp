/**@file
 * @brief     Vectors of complex numbers.
 * @author    Igor Lesik 2020
 * @copyright Igor Lesik 2020
 *
 */
#pragma once

#include "vxtypes.hpp"
#include "vxops.hpp"

namespace vx::cx {

template <typename V>
struct Complex
{
    V real;
    V img;

    using type = V;
};

/// Add complex numbers.
///
/// Addition is rather obvious - it adds pairs componentwise:
/// `(a₁, b₁) + (a₂, b₂) = (a₁ + a₂ , b₁ + b₂)`
///
template <typename CV>
CV add(const CV& cv1, const CV& cv2)
{
    CV res{
        real: vx::add(cv1.real, cv2.real),
        img:  vx::add(cv1.img,  cv2.img)};

    return res;
}

template <typename CV>
CV sub(const CV& cv1, const CV& cv2)
{
    CV res{
        real: vx::sub(cv1.real, cv2.real),
        img:  vx::sub(cv1.img,  cv2.img)};

    return res;
}

/// Inverse (a,b) -> (-a,-b)
template <typename CV>
CV inverse(const CV& cv)
{
    return CV{real: vx::inverse(cv.real), img: vx::inverse(cv.img)};
}

/// Changing the sign of the imaginary part only is known as conjugation.
///
/// Two numbers related by conjugation are said to be complex conjugates of each other.
///
template <typename CV>
CV conj(const CV& cv)
{
    return CV{real: cv.real, img: vx::inverse(cv.img)};
}

/// fill_zero
template <typename CV>
void fill_zero(CV& cv)
{
    vx::fill_zero(cv.real);
    vx::fill_zero(cv.img);
}

/// zero vector
template <typename CV>
CV zero_vector()
{
    CV zero;
    fill_zero(zero);
    return zero;
}

/// (a₁, b₁) × (a₂, b₂) = (a₁a₂ − b₁b₂, a₁b₂ + a₂b₁)
///
/// ```
/// r1=a1,...  r2=a2,...
/// i1=b1,...  i2=b2,...
///
/// vk = r1[n]*r2[n], vm = r1[n]*i2[n]
/// vl = i1[n]*i2[n], vn = r2[n]*i1[n]
/// res_r = vk - vl, res_i = vm + vn
/// ```
template <typename CV>
CV mul(const CV& cv1, const CV& cv2)
{
    typename CV::type vk{vx::mul(cv1.real, cv2.real)};
    typename CV::type vl{vx::mul(cv1.img,  cv2.img)};
    typename CV::type vm{vx::mul(cv1.real, cv2.img)};
    typename CV::type vn{vx::mul(cv1.img,  cv2.real)};

    CV res{
        real: vx::sub(vk, vl),
        img:  vx::add(vm, vn)};

    return res;
}

//modulus
// |a + bi| = sqrt(a^2 + b^2)
/*template <typename CV>
CV::type modulus(const CV& cv)
{
    typename CV::type r2{vx::mul(cv.real, cv.real)};
    typename CV::type i2{vx::mul(cv.img,  cv.img)};
    typename CV::type s{vx::sum(r2, i2)};
    typename CV::type res{vx::sqrt(s)};

    return res;
}*/


//div
//(a1,b1)/(a2,b2)=((a1a2 + b1b2)/(a2^2 + b2^2),(a2b1 - a1b2)/(a2^2 + b2^2))


//cartesian2polar

//polar2cartesian

//mul_scalar

} //namespace vx::cx
