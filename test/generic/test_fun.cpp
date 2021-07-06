#include <cstdlib>
#include <cstdint>
#include <cassert>
#include <type_traits>

#include "vx/vxtypes.hpp"
#include "vx/vxops.hpp"
#include "vx/vxfun.hpp"

static bool test_dot()
{
    using namespace vx;

#ifdef __AVX__
    F64x4 a{1,2,3,4};
    F64x4 b{5,6,7,8};
    double c = vx::dot<double>(a, b);
    assert(c == (1.0*5.0 + 2.0*6.0 + 3.0*7.0 + 4.0*8.0));
#else
    F64x2 a{1,2};
    F64x2 b{5,6,};
    double c = vx::dot<double>(a, b);
    assert(c == (1.0*5.0 + 2.0*6.0));
#endif
    return true;
}

static bool test_inverse()
{
    using namespace vx;

    I32x4 a{1,-2,3,-4};
    I32x4 a_inv = vx::inverse(a);
    assert(vx::equal(a_inv, I32x4{-1,2,-3,4}));

    F32x4 b{1,-2,3,-4};
    F32x4 b_inv = vx::inverse(b);
    assert(vx::equal(b_inv, F32x4{-1,2,-3,4}));

    return true;
}

using TestFun = bool (*)();

static TestFun tests[] = {
    test_dot, test_inverse
};

int main(int, char**)
{
    for (auto test : tests) {
        if (!test()) return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}