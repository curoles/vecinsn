#include <cstdlib>
#include <cassert>
#include <cstdio>

#include "vecinsn.hpp"

using namespace vx;

static bool test1()
{
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

static bool test2()
{
    static_assert(nrelem<U32x2>() == 2 and sizeof(U32x2) ==  8);
    static_assert(nrelem<U32x4>() == 4 and sizeof(U32x4) == 16);
    static_assert(nrelem<U32x8>() == 8 and sizeof(U32x8) == 32);
    static_assert(nrelem<U64x8>() == 8 and sizeof(U64x8) == 64);
    V8ui a = {1,2,3,4,5,6,7,8};
    assert(sum<uint32_t>(a) == (1+2+3+4+5+6+7+8));
    U32x2 b = {1,2};
    assert(sum<uint32_t>(b) == (1+2));
    assert(equal(b + 1, (U32x2){2,3}));
    assert(!equal(b - 1, (U32x2){2,3}));

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
    Fx4 a = {1.1, 2.2, 3.3, 4.4};
    U32x4 mask = {3, 2, 1, 0};
    assert(equal(shuffle(a, mask),(Fx4){4.4, 3.3, 2.2, 1.1}));

    Fx4 b = {5.5, 6.6, 7.7, 8.8};
    U32x4 mask2 = {3, 5, 6, 0};
    assert(equal(shuffle(a, b, mask2),(Fx4){4.4, 6.6, 7.7, 1.1}));

#if __GNUC__ > 8
    assert(equal(convert<I32x4>(a), (I32x4){1,2,3,4}));
#endif

    return true;
}

static bool test__all_ones()
{
    assert(test_all_ones(true_vec<U32x4>()));
    assert(test_all_zeros(false_vec<U32x4>()));

    assert(test_all_ones((I64x2){-1L,-1L}));
    assert(!test_all_ones((I64x2){-1L,0L}));
    assert(!test_all_zeros((I64x2){-1L,0L}));
    assert(test_all_zeros((I64x2){0L,0L}));

    return true;
}

static bool test_fill()
{
    U32x4 a;
    fill_zero(a);
    assert(test_all_zeros(a));

    fill(a, ~0u);
    assert(test_all_ones(a));

    fill(a, 7u);
    assert(!test_all_ones(a));
    assert(equal(a, (U32x4){7,7,7,7}));
    assert(!equal(a, (U32x4){7,77,7,7}));

    return true;
}

using TestFun = bool (*)();

static TestFun tests[] = {
    test1, test2, test_shuffle, test__all_ones, test_fill
};

int main(int, char**)
{
    for (auto test : tests) {
        if (!test()) return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
