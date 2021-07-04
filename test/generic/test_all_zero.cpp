#include <cstdlib>
#include <cstdint>
#include <cassert>
#include <type_traits>

#include "vx/vxtypes.hpp"
#include "vx/vxops.hpp"

static bool test_all_zero()
{
    using namespace vx;

    assert(vx::test_all_ones(vx::true_vec<U32x4>()));
    assert(vx::test_all_zeros(vx::false_vec<U32x4>()));

    assert(vx::test_all_ones((I64x2){-1L,-1L}));
    assert(!vx::test_all_ones((I64x2){-1L,0L}));
    assert(!vx::test_all_zeros((I64x2){-1L,0L}));
    assert(vx::test_all_zeros((I64x2){0L,0L}));

    return true;
}

using TestFun = bool (*)();

static TestFun tests[] = {
    test_all_zero
};

int main(int, char**)
{
    for (auto test : tests) {
        if (!test()) return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}