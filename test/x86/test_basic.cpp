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


static bool test_array()
{
    vx::Array<int16_t, 4, 2> a {ar: {{1,2,3,4},{5,6,7,8}}};
    vx::Array<int16_t, 4, 2> b {ar: {{4,3,2,1},{8,7,5,6}}};
    assert(a.ar[1][1] == 6);
    assert(a[6] == 7);

    a.add(b);
    assert(a[6] == (7+5));

    a.sub(b);
    assert(a[6] == 7);

    return true;
}




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
