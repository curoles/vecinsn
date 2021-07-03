#include <cstdlib>
#include <cstdint>
#include <cassert>
#include <type_traits>

#include "vx/x86/vxtypes.hpp"

static bool test_type_maker()
{
    vx::make<float,8>::type dyno;
    static_assert(std::is_same<vx::Fx8, decltype(dyno)>::value);

    vx::make<int16_t,4>::type dyno2;
    static_assert(std::is_same<vx::I16x4, decltype(dyno2)>::value);

    return true;
}

using TestFun = bool (*)();

static TestFun tests[] = {
    test_type_maker
};

int main(int, char**)
{
    for (auto test : tests) {
        if (!test()) return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}