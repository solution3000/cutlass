/***************************************************************************************************
 * Copyright (c) 2017-2020, NVIDIA CORPORATION.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted
 * provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright notice, this list of
 *       conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright notice, this list of
 *       conditions and the following disclaimer in the documentation and/or other materials
 *       provided with the distribution.
 *     * Neither the name of the NVIDIA CORPORATION nor the names of its contributors may be used
 *       to endorse or promote products derived from this software without specific prior written
 *       permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL NVIDIA CORPORATION BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TOR (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 **************************************************************************************************/
/*! \file
    \brief Templates exposing architecture support for multiply-add operations
*/

#pragma once

#include "cutlass/array.h"
#include "cutlass/numeric_types.h"

#include "cutlass/gemm/gemm.h"
#include "cutlass/arch/arch.h"

/////////////////////////////////////////////////////////////////////////////////////////////////

namespace cutlass {
namespace arch {

/////////////////////////////////////////////////////////////////////////////////////////////////

/// Tag indicating the operation implied by MMA.
struct OpMultiplyAdd;

/////////////////////////////////////////////////////////////////////////////////////////////////

/// Tag indicating the result is saturated to MAX_FLOAT|MIN_FLOAT or MAX_INT|MIN_INT
struct OpMultiplyAddSaturate;

/////////////////////////////////////////////////////////////////////////////////////////////////

/// Tag indicating the input is converted to a narrower type (BF16)
struct OpMultiplyAddFastBF16;

/////////////////////////////////////////////////////////////////////////////////////////////////

/// Tag indicating the input is converted to a narrower type (F16)
struct OpMultiplyAddFastF16;

/////////////////////////////////////////////////////////////////////////////////////////////////

/// Tag indicating the complex multiply-add operation
struct OpMultiplyAddComplex;

/////////////////////////////////////////////////////////////////////////////////////////////////

/// Tag indicating the gaussian complex multiply-add operation
struct OpMultiplyAddGaussianComplex;

/////////////////////////////////////////////////////////////////////////////////////////////////

/// Tag indicating the inner product is defined by (XOR, POPC)
struct OpXorPopc;

/////////////////////////////////////////////////////////////////////////////////////////////////

/// Tag classifying math operators as thread-level operations.
struct OpClassSimt;

/////////////////////////////////////////////////////////////////////////////////////////////////

/// Tag classifing operators as Tensor Core operations.
struct OpClassTensorOp;

/////////////////////////////////////////////////////////////////////////////////////////////////
/// Tag classifing operators as WMMA Tensor Core operations
struct OpClassWmmaTensorOp;

/////////////////////////////////////////////////////////////////////////////////////////////////

/// Matrix multiply-add operation
template <
  /// Size of the matrix product (concept: GemmShape)
  typename Shape_,
  /// Number of threads participating
  int kThreads_,
  /// Data type of A elements
  typename ElementA,
  /// Layout of A matrix (concept: MatrixLayout)
  typename LayoutA,
  /// Data type of B elements
  typename ElementB,
  /// Layout of B matrix (concept: MatrixLayout)
  typename LayoutB,
  /// Element type of C matrix
  typename ElementC,
  /// Layout of C matrix (concept: MatrixLayout)
  typename LayoutC,
  /// Inner product operator
  typename Operator
>
struct Mma;

/////////////////////////////////////////////////////////////////////////////////////////////////

/// Matrix multiply-add operation - specialized for 1x1x1x1 matrix multiply operation
template <
  /// Data type of A elements
  typename ElementA,
  /// Layout of A matrix (concept: MatrixLayout)
  typename LayoutA,
  /// Data type of B elements
  typename ElementB,
  /// Layout of B matrix (concept: MatrixLayout)
  typename LayoutB,
  /// Element type of C matrix
  typename ElementC,
  /// Layout of C matrix (concept: MatrixLayout)
  typename LayoutC,
  /// Inner product operator
  typename Operator
>
struct Mma<gemm::GemmShape<1, 1, 1>, 1, ElementA, LayoutA, ElementB, LayoutB, ElementC, LayoutC, Operator> {

  using Shape = gemm::GemmShape<1, 1, 1>;

  CUTLASS_HOST_DEVICE
  void operator()(
    Array<ElementC, 1> &d,
    Array<ElementA, 1> const &a,
    Array<ElementB, 1> const &b,
    Array<ElementC, 1> const &c
  ) {

    d[0] = a[0] * b[0] + c[0];
  }
};

/////////////////////////////////////////////////////////////////////////////////////////////////

} // namespace arch
} // namespace cutlass

/////////////////////////////////////////////////////////////////////////////////////////////////

//
// Specializations for each compute capability
//

#include "cutlass/arch/mma_sm50.h"
#include "cutlass/arch/mma_sm60.h"
#include "cutlass/arch/mma_sm61.h"
#include "cutlass/arch/mma_sm70.h" 
#include "cutlass/arch/mma_sm75.h" 
#include "cutlass/arch/mma_sm80.h"
/////////////////////////////////////////////////////////////////////////////////////////////////
