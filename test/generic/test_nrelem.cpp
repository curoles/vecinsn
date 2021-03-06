#include <cstdlib>
#include <cstdint>
#include <cassert>
#include <type_traits>

#include "vx/vxtypes.hpp"

static bool test_nrelem()
{
    using namespace vx;

    static_assert(nrelem<F64x8>() == 8 and sizeof(F64x8) == 64);
    static_assert(nrelem<U32x4>() == 4 and sizeof(U32x4) == 16);
    static_assert(nrelem<U32x8>() == 8 and sizeof(U32x8) == 32);
    static_assert(nrelem<U64x8>() == 8 and sizeof(U64x8) == 64);

    return true;
}

using TestFun = bool (*)();

static TestFun tests[] = {
    test_nrelem
};

int main(int, char**)
{
    for (auto test : tests) {
        if (!test()) return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}