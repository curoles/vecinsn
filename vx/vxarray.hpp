/**@file
 * @brief     An array of Vectors that looks like vector of base-type elements.
 * @author    Igor Lesik 2020
 * @copyright Igor Lesik 2020
 *
 *
 *
 */
#pragma once

#include "vx/vxtypes.hpp"
#include "vx/vxops.hpp"
#include "vx/vxfun.hpp"

/// Namespace of all vector types and functions.
///
namespace vx {

/// Array of Vectors that pretends to be a vector of base-type elements.
///
template <typename T, std::size_t Sz>
struct array
{
    static constexpr std::size_t PSz =
        recommended_vector_size_for_array<T, Sz>() / sizeof(T);

    static constexpr std::size_t Cnt = (Sz + PSz - 1)/ PSz;

    using value_type = T;
    using reference = value_type&;

    using pv_type = typename vx::make<T, PSz>::type; ///< type of the packed vector

    pv_type pv[Cnt];

    array(const array&) = default;

    array& operator=(const array&) = default;

    /// Returns reference to n-th element.
    T& operator[](std::size_t i) const {
        return pv[i/PSz][i%PSz];
    }

    /// Adds `this[n] += other[n]`.
    ///
    /// ```c++
    /// vx::array<int16_t, 8> a {pv: {{1,2,3,4,5,6,7,8}}};
    /// vx::array<int16_t, 8> b {pv: {{4,3,2,1,8,7,5,6}}};
    /// a.add(b);
    /// assert(a[6] == (7+5));
    /// ```
    array& add(const array& other) {
        for (std::size_t chunk = 0; chunk < Cnt; ++chunk) {
            pv[chunk] = vx::add(pv[chunk], other.pv[chunk]);
        }
        return *this;
    }

    /// Subs `this[n] -= other[n]`.
    array& sub(const array& other) {
        for (std::size_t chunk = 0; chunk < Cnt; ++chunk) {
            pv[chunk] = vx::sub(pv[chunk], other.pv[chunk]);
        }
        return *this;
    }

};


} // namespace vx
