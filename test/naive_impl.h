#ifndef NAIVE_IMPL_H
#define NAIVE_IMPL_H

#include <stddef.h>

int check_conv2d(
    const float *O,
    const float *I,
    const float *K,
    const float *actual,
    size_t h, size_t w, size_t c,
    size_t kh, size_t kw, size_t kc,
    size_t sh, size_t sw,
    size_t pt, size_t pb, size_t pl, size_t pr,
    size_t dh, size_t dw,
    float tolerance);

int check_conv2d_nchw(
    const float *O,
    const float *I,
    const float *K,
    const float *actual,
    size_t h, size_t w, size_t c,
    size_t kh, size_t kw, size_t kc,
    size_t sh, size_t sw,
    size_t pt, size_t pb, size_t pl, size_t pr,
    size_t dh, size_t dw,
    float tolerance);

int check_himeno(
    const float *A,
    const float *B,
    const float *C,
    const float *BND,
    const float *WRK1,
    const float *WRK2,
    const float *P,
    float omega,
    float gosa,
    size_t I, size_t J, size_t K,
    float tolerance);

#endif  // NAIVE_IMPL_H
