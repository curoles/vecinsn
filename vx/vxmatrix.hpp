/**@file
 * @brief     Matrix operations with Vector eXtentions.
 * @author    Igor Lesik 2020
 * @copyright Igor Lesik 2020
 *
 *
 */
#pragma once

#include <cstdint>

#include "vxtypes.hpp"
#include "vxops.hpp"
#include "vxadvops.hpp"

namespace vx::mx {

using Index = uint64_t;

template <typename T>
struct Matrix
{
    const Index nrCols, nrRows, nrEl;
    const bool ownsData;
    T* data;

    Matrix():
        nrCols(0), nrRows(0), nrEl(0),
        ownsData(false), data(nullptr)
    {}

    Matrix(T* dataPtr, Index cols, Index rows):
        nrCols(cols), nrRows(rows), nrEl(cols*rows),
        ownsData(false), data(dataPtr)
    {}

    Matrix(Index cols, Index rows):
        nrCols(cols), nrRows(rows), nrEl(cols*rows),
        ownsData(true), data(new T[nrEl])
    {}

   ~Matrix() {
        if (ownsData) delete[] data;
    }

    T& at(Index col, Index row) {return data[row*nrCols + col];}

    const T& at(Index col, Index row) const {return data[row*nrCols + col];}
};

template <typename T>
void add(Matrix<T>& a, const Matrix<T>& b)
{
    assert(a.nrCols == b.nrCols and a.nrRows == b.nrRows);

    for (Index i = 0; i < a.nrEl; ++i) {
        a.data[i] += b.data[i];
    }
}

template <Index chunkSz, typename T>
void addBy(Matrix<T>& a, const Matrix<T>& b)
{
    assert(a.nrCols == b.nrCols and a.nrRows == b.nrRows);

    using Chunk = typename vx::make<T,chunkSz>::type;

    Chunk ta, tb, tc;

    Index nrChunks = a.nrEl / chunkSz;

    for (Index ch = 0; ch < nrChunks; ++ch) {
        vx::load(ta, &a.data[ch*chunkSz]);
        vx::load(tb, &b.data[ch*chunkSz]);
        tc = vx::add(ta, tb);
        vx::store(&a.data[ch*chunkSz], tc);
    }
}


///
///
/// ```
///    m            n
///  aaa     n   cccc
///  aaa  bbbb   cccc
///  aaa  bbbb = cccc
///  aaa mbbbb   cccc
/// laaa        lcccc
/// ```
/// A x B = C
/// Number of columns in the A must be equal to the number
/// of rows in the B.
/// C(i,j) is obtained by multiplying term-by-term the entries
/// of the i-th row of A and the j-th column of B, and summing
/// these n products.
template <typename T>
void mul(Matrix<T>& c, const Matrix<T>& a, const Matrix<T>& b)
{
    assert(a.nrCols == b.nrRows);
    assert(c.nrCols == b.nrCols and c.nrRows == a.nrRows);

    for (Index row = 0; row < a.nrRows; ++row) {
        for (Index col = 0; col < b.nrCols; ++col) {
            c.at(col, row) = 0;
            for (Index i = 0; i < a.nrCols; ++i) {
                c.at(col, row) += a.at(i, row) * b.at(col, i);
            }
        }
    }
}

#ifdef __AVX2__
template <Index chunkSz, typename T>
void mulBy(Matrix<T>& c, const Matrix<T>& a, const Matrix<T>& b)
{
    assert(a.nrCols == b.nrRows);
    assert(c.nrCols == b.nrCols and c.nrRows == a.nrRows);

    using Chunk = typename vx::make<T,chunkSz>::type;
    using GatherVec = typename vx::make<int64_t,chunkSz>::type;
    Chunk ta, tb;

    GatherVec gather;
    for (unsigned int i = 0; i < chunkSz; ++i) {gather[i] = i*b.nrCols;}

    for (Index row = 0; row < a.nrRows; ++row) {
        for (Index col = 0; col < b.nrCols; ++col) {
            c.at(col, row) = 0;
            for (Index i = 0; i < a.nrCols; i += chunkSz) {
                vx::load(ta, &a.data[row*a.nrCols + i]);
                vx::load_gather(tb, &b.data[i*b.nrCols + col], gather, sizeof(T));

                c.at(col, row) += vx::dot<T>(ta, tb);
            }
        }
    }
}
#endif

} // namespace vx::mx
