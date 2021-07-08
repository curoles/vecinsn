#include <cstdlib>
#include <cstdint>
#include <cassert>
#include <cmath>
#include <type_traits>

#include "vx/vxarray.hpp"

static bool test_array()
{
    using namespace vx;

    vx::array<int16_t, 8> a {1,2,3,4,5,6,7,8};
    vx::array<int16_t, 8> b {4,3,2,1,8,7,5,6};

    static_assert(a.PSz == 8 and a.Cnt == 1);

    assert(a.data()[0][5] == 6);
    assert(a[6] == 7);

    a.add(b);
    assert(a[6] == (7+5));

    a.sub(b);
    assert(a[6] == 7);

    auto c = a + b;
    assert(c.at(7) == (8+6));

    c[3] = 777;
    assert(c[3] == 777);

    return true;
}

#if 0
template<class T>
typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type
almost_equal(T x, T y, unsigned int ulp)
{
    // the machine epsilon has to be scaled to the magnitude of the values used
    // and multiplied by the desired precision in ULPs (units in the last place)
    return std::fabs(x-y) <= std::numeric_limits<T>::epsilon() * std::fabs(x+y) * ulp
        // unless the result is subnormal
        || std::fabs(x-y) < std::numeric_limits<T>::min();
}
#endif

static bool test_array_forloop()
{
    using namespace vx;

    vx::array<float, 8> d;
    d.fill(777.123);

    for (const auto v : d) {
        //printf("%f\n", v);
        assert(std::fabs(v - 777.123) < 0.001);
    }

    vx::array<uint32_t, 4> e;
    e.fill(0);
    auto it = e.begin();
    ++it; ++it;
    *it = 123;
    assert(e[0]==0 && e[1]==0 && e[2]==123);

    return true;
}

using TestFun = bool (*)();

static TestFun tests[] = {
    test_array, test_array_forloop
};

int main(int, char**)
{
    for (auto test : tests) {
        if (!test()) return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}