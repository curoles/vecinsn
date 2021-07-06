#include <cstdlib>
#include <cstdint>
#include <cassert>
#include <type_traits>

#include "vx/vxarray.hpp"

static bool test_array()
{
    using namespace vx;

    vx::array<int16_t, 8> a {pv: {{1,2,3,4,5,6,7,8}}};
    vx::array<int16_t, 8> b {pv: {{4,3,2,1,8,7,5,6}}};

    static_assert(a.PSz == 8 and a.Cnt == 1);

    assert(a.pv[0][5] == 6);
    assert(a[6] == 7);

    a.add(b);
    assert(a[6] == (7+5));

    a.sub(b);
    assert(a[6] == 7);

    return true;
}

using TestFun = bool (*)();

static TestFun tests[] = {
    test_array
};

int main(int, char**)
{
    for (auto test : tests) {
        if (!test()) return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}