/*
 Copyright (C) 2011  The Autonomous Systems Lab, ETH Zurich,
 Stefan Leutenegger, Simon Lynen and Margarita Chli.

 Copyright (C) 2013  The Autonomous Systems Lab, ETH Zurich,
 Stefan Leutenegger and Simon Lynen.

 All rights reserved.

 This is the Author's implementation of BRISK: Binary Robust Invariant
 Scalable Keypoints [1]. Various (partly unpublished) extensions are provided,
 some of which are described in [2].

 [1] Stefan Leutenegger, Margarita Chli and Roland Siegwart. BRISK: Binary
     Robust Invariant Scalable Keypoints. In Proceedings of the IEEE
     International Conference on Computer Vision (ICCV), 2011.

 [2] Stefan Leutenegger. Unmanned Solar Airplanes: Design and Algorithms for
     Efficient and Robust Autonomous Operation. Doctoral dissertation, 2014.

 This file is part of BRISK.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
 * Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.
 * Neither the name of the Autonomous Systems Lab, ETH Zurich nor the
   names of its contributors may be used to endorse or promote products
   derived from this software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY
 DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef INTERNAL_VECTORIZED_FILTERS_H_
#define INTERNAL_VECTORIZED_FILTERS_H_

#include <agast/wrap-opencv.h>
#include <brisk/internal/macros.h>

#ifdef __ARM_NEON__
  // Not implemented.
#else
namespace brisk {
// Generic SSE-optimized 2D filter on CV_8U/CV_16S matrices. stores result in
// CV_16S matrix.
template<int X, int Y>
__inline__ void Filter2D(cv::Mat& src, cv::Mat& dst, cv::Mat& kernel);  // NOLINT

// Generic SSE-optimized 2D filter CV_8U to CV_16S.
template<int X, int Y>
__inline__ void Filter2D8U(cv::Mat& src, cv::Mat& dst, cv::Mat& kernel);  // NOLINT

// Generic SSE-optimized 2D filter CV_16S to CV_16S.
template<int X, int Y>
__inline__ void Filter2D16S(cv::Mat& src, cv::Mat& dst, cv::Mat& kernel);  // NOLINT

// 3-by-3 box filter CV_16S to CV_16S.
__inline__ void FilterBox3by316S(cv::Mat& src, cv::Mat& dst);  // NOLINT

// 3-by-3 Gaussian filter CV_16S to CV_16S.
void FilterGauss3by316S(cv::Mat& src, cv::Mat& dst);  // NOLINT

// 3-by-3 Gaussian filter CV_32F to CV_32F.
void FilterGauss3by332F(cv::Mat& src, cv::Mat& dst);  // NOLINT

}  // namespace brisk
#include "./vectorized-filters-inl.h"
#endif  // __ARM_NEON__
#endif  // INTERNAL_VECTORIZED_FILTERS_H_
