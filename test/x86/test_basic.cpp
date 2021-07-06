#include <cstdlib>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <type_traits>

#include "vx/vxtypes.hpp"
#include "vx/vxops.hpp"
#include "vx/vxadvops.hpp"
#include "vx/vxarray.hpp"
#include "vx/vxcomplex.hpp"

using namespace vx;


using TestFun = bool (*)();

static TestFun tests[] = {
    test_type_maker, test_normal_ops, test_nrelem, test_logic,
    test_shuffle, test__all_ones, test_fill,
    test_load,
    test_array,
    test_complex1, test_complex2,
    test_dot, test_inverse
};

int main(int, char**)
{
    for (auto test : tests) {
        if (!test()) return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
