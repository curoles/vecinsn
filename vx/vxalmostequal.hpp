/**@file
 * @brief     Check if 2 floating point numbers are close.
 * @author    Igor Lesik 2020-2021
 * @copyright Igor Lesik 2020-2021
 *
 */
#pragma once

#include <cmath>
#include <type_traits>

namespace vx {

template<typename T>
typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type
float_almost_equal(T x, T y, unsigned int ulp)
{
    // the machine epsilon has to be scaled to the magnitude of the values used
    // and multiplied by the desired precision in ULPs (units in the last place)
    return std::fabs(x-y) <= std::numeric_limits<T>::epsilon() * std::fabs(x+y) * ulp
        // unless the result is subnormal
        || std::fabs(x-y) < std::numeric_limits<T>::min();
}

template<typename C>
bool container_values_almost_equal(
    const C& c,
    const typename C::value_type v,
    unsigned int ulp
)
{
    for (typename C::const_iterator it = c.cbegin(); it != c.cend(); ++it) {
        if (!float_almost_equal(*it, v, ulp)) {
            return false;
        }
    }

    return true;
}

template<typename C>
bool containers_values_almost_equal(
    const C& c1,
    const C& c2,
    unsigned int ulp)
{
    for (typename C::const_iterator it1 = c1.cbegin(), it2 = c2.cbegin();
       it1 != c1.cend() && it2 != c2.cend();
       ++it1, ++it2)
    {
        if (!float_almost_equal(*it1, *it2, ulp)) {
            return false;
        }
    }

    return true;
}

} // namespace vx
