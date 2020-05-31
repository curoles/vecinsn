#include <cstdlib>
#include <cassert>
#include <cstdio>
#include <cstring>

#include "vx/vxmatrix.hpp"

static bool test_add()
{
    double a[] = {1,2,  3,4,  5,6};
    double b[] = {9,8,  7,6,  5,4};
    vx::mx::Matrix<double> ma(a, 2, 3);
    vx::mx::Matrix<double> mb(b, 2, 3);

    vx::mx::add(ma, mb);

    assert(ma.at(0,0) == (1.0 + 9.0));
    assert(ma.at(1,2) == (6.0 + 4.0));

    return true;
}

using TestFun = bool (*)();

static TestFun tests[] = {
    test_add
};

int main(int, char**)
{
    for (auto test : tests) {
        if (!test()) return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
