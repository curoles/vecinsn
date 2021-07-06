#include <cstdlib>
#include <cstdint>
#include <cassert>
#include <type_traits>

#include "vx/vxtypes.hpp"
#include "vx/vxcomplex.hpp"


static bool test_complex1()
{
    using CV = vx::cx::Complex<vx::I64x2>;
    CV v1{real: {1,2}, img:{3,4}};
    CV v2{real: {5,6}, img:{7,8}};

    CV v3 = vx::cx::add(v1, v2);
    assert(v3.real[0] == 1+5 and v3.real[1] == 2+6);
    assert(v3.img [0] == 3+7 and v3.img[1]  == 4+8);

    return true;
}

static bool test_complex2()
{
    using CV = vx::cx::Complex<vx::F64x2>;
    CV v1{real: {1,2}, img:{3,4}};
    CV v2{real: {5,6}, img:{7,8}};

    CV v3 = vx::cx::add(v1, v2);
    assert(v3.real[0] == 1+5 and v3.real[1] == 2+6);
    assert(v3.img [0] == 3+7 and v3.img[1]  == 4+8);

    CV v4 = vx::cx::mul(v1, v2);
    assert(v4.real[0] == (1.0*5 - 3.0*7));
    assert(v4.img [0] == (1.0*7 + 5.0*3));

    return true;
}

using TestFun = bool (*)();

static TestFun tests[] = {
    test_complex1, test_complex2
};

int main(int, char**)
{
    for (auto test : tests) {
        if (!test()) return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}