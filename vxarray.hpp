/**@file
 * @brief     An array of Vectors that looks like vector of base-type elements.
 * @author    Igor Lesik 2020
 * @copyright Igor Lesik 2020
 *
 *
 *
 */
#pragma once

#include "vxtypes.hpp"
#include "vxops.hpp"

/// Namespace of all vector types and functions.
///
namespace vx {


/// Array of Vectors that pretends to be a vector of base-type elements.
///
template <typename T, unsigned PSz, unsigned Cnt>
struct Array
{
    static constexpr unsigned Sz = PSz * Cnt; ///< total size, number of all elements
    using pv_type = typename vx::make<T, PSz>::type; ///< type of the packed vector

    pv_type ar[Cnt];

    /// Returns reference to n-th element.
    T& operator[](unsigned int i) { return ar[i/PSz][i%PSz]; }

    /// Adds `this[n] += other[n]`.
    ///
    /// ```c++
    /// vx::Array<int16_t, 4, 2> a {ar: {{1,2,3,4},{5,6,7,8}}};
    /// vx::Array<int16_t, 4, 2> b {ar: {{4,3,2,1},{8,7,5,6}}};
    /// a.add(b);
    /// assert(a[6] == (7+5));
    /// ```
    void add(const Array& other) {
        for (unsigned chunk = 0; chunk < Cnt; ++chunk) {
            ar[chunk] = vx::add(ar[chunk], other.ar[chunk]);
        }
    }

    /// Subs `this[n] -= other[n]`.
    void sub(const Array& other) {
        for (unsigned chunk = 0; chunk < Cnt; ++chunk) {
            ar[chunk] = vx::sub(ar[chunk], other.ar[chunk]);
        }
    }

};


} // namespace vx
