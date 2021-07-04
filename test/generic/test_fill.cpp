#include <cstdlib>
#include <cstdint>
#include <cassert>
#include <type_traits>

#include "vx/vxtypes.hpp"
#include "vx/vxops.hpp"

static bool test_fill()
{
    using namespace vx;

    U32x4 a;
    fill_zero(a);
    assert(test_all_zeros(a));

    fill(a, ~0u);
    assert(test_all_ones(a));

    fill(a, 7u);
    assert(!test_all_ones(a));
    assert(equal(a, (U32x4){7,7,7,7}));
    assert(!equal(a, (U32x4){7,77,7,7}));
    a[2] = 8; // set single element value
    assert(equal(a, (U32x4){7,7,8,7}));

    return true;
}

using TestFun = bool (*)();

static TestFun tests[] = {
    test_fill
};

int main(int, char**)
{
    for (auto test : tests) {
        if (!test()) return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}