/**@file
 * @brief     An array of Vectors that looks like vector of base-type elements.
 * @author    Igor Lesik 2020
 * @copyright Igor Lesik 2020
 *
 *
 *
 */
#pragma once

#include <stdexcept>
#include <iterator>

#include "vx/vxtypes.hpp"
#include "vx/vxops.hpp"
#include "vx/vxfun.hpp"

/// Namespace of all vector types and functions.
///
namespace vx {

/// Array of Vectors that pretends to be a vector of base-type elements.
///
template <typename T, std::size_t Sz>
class array
{
public:
    static constexpr std::size_t PSz =
        recommended_vector_size_for_array<T, Sz>() / sizeof(T);

    static constexpr std::size_t Cnt = (Sz + PSz - 1)/ PSz;

    using value_type = T;
    using reference = value_type&;
    using const_reference = const reference;
    using size_type = std::size_t;

    using pv_type = typename vx::make<T, PSz>::type; ///< type of the packed vector
    using pv_array = pv_type[Cnt];

private:
    pv_type pv[Cnt];


public:
    array() = default;
    array(const array&) = default;

    array(std::initializer_list<T> list) {
        for (std::size_t pos = 0; const T v : list) {
            at(pos++) = v;
        }
    }

    array& operator=(const array&) = default;

    pv_array& data() {return pv;}

    /// Returns reference to n-th element.
    reference operator[](std::size_t pos) {
        return pv[pos/PSz][pos%PSz];
    }

    const_reference operator[](std::size_t pos) const {
        return pv[pos/PSz][pos%PSz];
    }

    /// Returns a reference to the element at specified location pos,
    /// with bounds checking. 
    reference at(size_type pos) {
        if (pos >= Sz) throw std::out_of_range("vx::array");
        return operator[](pos);
    }

    const_reference at(size_type pos) const  {
        if (pos >= Sz) throw std::out_of_range("vx::array");
        return operator[](pos);
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

    /// Assigns the given value value to all elements in the container.
    void fill(const T& value) {
        for (std::size_t chunk = 0; chunk < Cnt; ++chunk) {
            vx::fill(pv[chunk], value);
        }
    }

    struct const_iterator
    {
        using iterator_category = std::forward_iterator_tag;
        //using difference_type   = std::ptrdiff_t;
        using value_type        = T;
        using pointer           = value_type*;
        using reference         = value_type&;

        const_iterator(vx::array<T,Sz>& ar, std::size_t pos):
            ar_(ar), pos_(pos) {}

        const reference operator*() const { return ar_.at(pos_); }
        //pointer operator->() { return ptr_; }
        const_iterator& /*prefix*/ operator++() { pos_++; return *this; }
        const_iterator operator++(int) {
            const_iterator tmp = *this; ++(*this); return tmp; }

        friend bool operator== (const const_iterator& a, const const_iterator& b) {
            return a.pos_ == b.pos_;
        };
        friend bool operator!= (const const_iterator& a, const const_iterator& b) {
            return a.pos_ != b.pos_;
        };

    private:
        vx::array<T,Sz>& ar_;
        std::size_t pos_;
    };

    const_iterator cbegin() { return const_iterator(*this, 0); }
    const_iterator cend()   { return const_iterator(*this, Sz); }

    const_iterator begin() { return const_iterator(*this, 0); }
    const_iterator end()   { return const_iterator(*this, Sz); }
};

template <typename T, std::size_t Sz>
vx::array<T, Sz> operator+(
    const vx::array<T, Sz>& first,
    const vx::array<T, Sz>& second
)
{
    vx::array<T,Sz> a(first);
    a.add(second);
    return a;
}


} // namespace vx
