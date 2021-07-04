#pragma once

#include "vxintrin.hpp"

namespace vx {

using namespace tvx;

using I16x8 = tvx::S16x8;

/// Returns 'false' vector {0,0,0,...}
template <typename T> constexpr T false_vec() { return (T){0}; }

/// Returns 'true' vector {-1,-1,-1,...}
template <typename T> constexpr T true_vec() { return !false_vec<T>(); }

} // end namespace vx