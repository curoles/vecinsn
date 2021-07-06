#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <cassert>
#include <type_traits>

#include "vx/vxtypes.hpp"
#include "vx/vxops.hpp"
#include "vx/vxfun.hpp"

static bool test_ops1()
{
    using namespace vx;

    V8ui a = {1,2,3,4,5,6,7,8};
    assert(vx::sum<uint32_t>(a) == (1+2+3+4+5+6+7+8));

    U32x2 b = {1,2};
    assert(sum<uint32_t>(b) == (1+2));
    assert(equal(b + 1, (U32x2){2,3}));
    assert(!equal(b - 1, (U32x2){2,3}));

    return true;
}

static bool test_ops2()
{
    using namespace vx;

    V4si a = {1,2,3,4};
    V4si b = {1,2,3,4};
    assert(equal(a, b));
    assert(equal(a - b, (V4si){0,0,0,0}));
    assert(equal(a + b, a * 2));
    assert(equal(a + b + b, a * 3));
    assert(equal((a + b)/2, a));
    assert(equal(a % 2, (V4si){1,0,1,0}));
    assert(equal(-a, (V4si){-1,-2,-3,-4}));
    assert(equal(a + 1, (V4si){2,3,4,5}));
    assert(equal(~a, (V4si){~1,~2,~3,~4}));
    assert(equal(a | b, a));
    assert(equal(a & b, a));
    assert(sum<uint32_t>(a) == (1+2+3+4));
    assert(equal(a << 1, (V4si){1<<1,2<<1,3<<1,4<<1}));
    assert(equal(a << b, (V4si){1<<1,2<<2,3<<3,4<<4}));

    return true;
}

static bool test_logic()
{
    using namespace vx;

    assert(equal(false_vec<I32x4>(), (I32x4){0,0,0,0}));
    assert(equal(true_vec<I32x4>(), (I32x4){-1,-1,-1,-1}));

    I32x4 c = {1,2,3,4};
    I32x4 z = {0};
    assert(equal(!!c, true_vec<I32x4>()));
    assert(equal(c && !z, true_vec<I32x4>()));

    return true;
}

static bool test_shuffle()
{
    using namespace vx;

    F32x4 a = {1.1, 2.2, 3.3, 4.4};
    U32x4 mask = {3, 2, 1, 0}; // reverse order
    assert(equal(shuffle(a, mask),(F32x4){4.4, 3.3, 2.2, 1.1}));

    F32x4 b = {5.5, 6.6, 7.7, 8.8};
    U32x4 mask2 = {3, 5, 6, 0}; // 1st 4 from a, 2nd 4 from b
    assert(equal(shuffle(a, b, mask2),(F32x4){4.4, 6.6, 7.7, 1.1}));

    // error: inner type must have the same size as inner type of the mask
    //U8x4 mask3{0,2,1,3};
    //assert(equal(shuffle(a, mask3),(Fx4){1.1, 3.3, 2.2, 4.4}));

#if __GNUC__ > 8
    assert(equal(convert<I32x4>(a), (I32x4){1,2,3,4}));
#endif

    return true;
}

static bool test_load()
{
    using namespace vx;

    F32x4 va;
    float a[4] = {1.1,2.2,3.3,4.4};
    vx::load(va, a);
    assert(equal(va, (F32x4){1.1,2.2,3.3,4.4}));
    a[1] = 22.22;
    std::memcpy(&va, a, sizeof va); // memcpy also works
    assert(equal(va, (F32x4){1.1,22.22,3.3,4.4}));
    va[2] = 33.33;
    vx::store(a, va);
    assert(a[2] == va[2]);

    return true;
}

using TestFun = bool (*)();

static TestFun tests[] = {
    test_ops1, test_ops2, test_logic,
    test_shuffle, test_load
};

int main(int, char**)
{
    for (auto test : tests) {
        if (!test()) return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}