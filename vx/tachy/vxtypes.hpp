#pragma once

#include "vxintrin.hpp"

namespace vx {

using namespace tvx;


/// Compile-time type maker.
///
/// Metaprogramming facility to dynamically construct Vector type in compile-time.
/// ```c++
/// vx::make<float,8>::type dyno;
/// static_assert(std::is_same<vx::F32x8, decltype(dyno)>::value);
/// ```
///
template <typename T, unsigned N> struct make {typedef void type;};

#define VX_DECL(count, type)  __attribute__ ((vector_size (count*sizeof(type))))

#define VX_DEF(Type,mn,count) \
using mn##x##count = Type VX_DECL(count, Type); \
template <> struct make<Type,count> {typedef vx::mn##x##count type;};

#define VX_DEF2(type,mn) VX_DEF(type,mn,2)
#define VX_DEF4(type,mn) VX_DEF(type,mn,4) VX_DEF2(type,mn)
#define VX_DEF8(type,mn) VX_DEF(type,mn,8) VX_DEF4(type,mn)
#define VX_DEF16(type,mn) VX_DEF(type,mn,16) VX_DEF8(type,mn)
#define VX_DEF32(type,mn) VX_DEF(type,mn,32) VX_DEF16(type,mn)
#define VX_DEF64(type,mn) VX_DEF(type,mn,64) VX_DEF32(type,mn)

VX_DEF64(  uint8_t,  U8)
VX_DEF64(   int8_t,  I8)
VX_DEF32( uint16_t, U16)
VX_DEF32(  int16_t, I16)
VX_DEF16( uint32_t, U32)
VX_DEF16(  int32_t, I32)
VX_DEF8 ( uint64_t, U64)
VX_DEF8 (  int64_t, I64)
//VX_DEF4 (uint128_t,U128)
//VX_DEF4 ( int128_t,I128)

VX_DEF16( float,F32)
VX_DEF8 (double,F64)

#undef VX_DECL
#undef VX_DEF
#undef VX_DEF2
#undef VX_DEF4
#undef VX_DEF8
#undef VX_DEF16
#undef VX_DEF32
#undef VX_DEF64

/// Returns 'false' vector {0,0,0,...}
template <typename T> constexpr T false_vec() { return (T){0}; }

/// Returns 'true' vector {-1,-1,-1,...}
template <typename T> constexpr T true_vec() { return !false_vec<T>(); }

} // end namespace vx