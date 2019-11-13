#ifndef INIT_H
#define INIT_H

#include <stddef.h>

void init_3d(float *arr,
             size_t D1, size_t D2, size_t D3);

void copy_3d(const float *src,
             float *dest,
             size_t D1, size_t D2, size_t D3);

void init_4d(float *arr,
             size_t D1, size_t D2, size_t D3, size_t D4);

#endif  // INIT_H
