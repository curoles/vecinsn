#include <cstdlib>
#include <cassert>
#include <cstdio>
#include <cstring>

#include "vx/vxmatrix.hpp"

static bool test_add2()
{
    double a[] = {1,2,  3,4,  5,6};
    double b[] = {9,8,  7,6,  5,4};
    vx::mx::Matrix<double> ma(a, 2, 3);
    vx::mx::Matrix<double> mb(b, 2, 3);

    vx::mx::add(ma, mb);

    assert(ma.at(0,0) == (1.0 + 9.0));
    assert(ma.at(1,2) == (6.0 + 4.0));

    vx::mx::addBy<2>(ma, mb);

    assert(ma.at(0,0) == (1.0 + 9.0 + 9.0));
    assert(ma.at(1,2) == (6.0 + 4.0 + 4.0));

    return true;
}

#if 0
static bool test_add4()
{
    double a[] = {1,2,  3,4,  5,6, 7,8};
    double b[] = {9,8,  7,6,  5,4, 3,2};
    vx::mx::Matrix<double> ma(a, 2, 4);
    vx::mx::Matrix<double> mb(b, 2, 4);

    vx::mx::addBy<4>(ma, mb);

    assert(ma.at(0,0) == (1.0 + 9.0 + 9.0));
    assert(ma.at(1,2) == (6.0 + 4.0 + 4.0));

    return true;
}
#endif

static bool test_mul2()
{
    double a[] = {1,2,  3,4,  5,6};
    double b[] = {9,8,7, 6,5,4};
    vx::mx::Matrix<double> ma(a, 2, 3);
    vx::mx::Matrix<double> mb(b, 3, 2);
    vx::mx::Matrix<double> mc(3, 3);

    vx::mx::mul(mc, ma, mb);

    assert(mc.at(0,0) == (1.0*9.0 + 2.0*6.0));

#ifdef __AVX2__
    vx::mx::Matrix<double> md(3, 3);

    vx::mx::mulBy<2>(md, ma, mb);

    for (unsigned col = 0; col < 3; ++col) {
        for (unsigned row = 0; row < 3; ++row) {
            assert(md.at(col,row) == mc.at(col,row));
        }
    }
#endif
    return true;
}

using TestFun = bool (*)();

static TestFun tests[] = {
    test_add2, test_mul2
   /*test_add4*/
};

int main(int, char**)
{
    for (auto test : tests) {
        if (!test()) return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
