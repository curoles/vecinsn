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
        ownsData(true), data(new T[nrCols*nrRows])
    {}

   ~Matrix() {
        if (ownsData) delete[] data;
    }

    T& at(Index col, Index row) {return data[row*nrCols + col];}
};

template <typename T>
void add(Matrix<T>& a, const Matrix<T>& b)
{
    assert(a.nrCols == b.nrCols and a.nrRows == b.nrRows);

    static constexpr unsigned nrElChunk = 2;
    using Chunk = typename vx::make<T,nrElChunk>::type;

    Chunk ta, tb, tc;

    Index nrChunks = a.nrEl / nrElChunk;

    for (Index ch = 0; ch < nrChunks; ++ch) {
        vx::load(ta, &a.data[ch*nrElChunk]);
        vx::load(tb, &b.data[ch*nrElChunk]);
        tc = vx::add(ta, tb);
        vx::store(&a.data[ch*nrElChunk], tc);
    }
}




} // namespace vx::mx
