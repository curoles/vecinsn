/**@file
 * @brief     Vectors of complex numbers.
 * @author    Igor Lesik 2020
 * @copyright Igor Lesik 2020
 *
 */
#pragma once

#include "vxtypes.hpp"
#include "vxops.hpp"

namespace vx::cmplx {

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

} //namespace vx::cmplx
