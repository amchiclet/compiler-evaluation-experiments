#include "util/init.h"

#include <stdlib.h>

float frand(float min, float max) {
  float scale = rand() / (float) RAND_MAX;
  return min + scale * (max - min);
}
void init_3d(
    float *arr,
    size_t D1, size_t D2, size_t D3) {
  size_t stride_D3 = 1;
  size_t stride_D2 = stride_D3 * D3;
  size_t stride_D1 = stride_D2 * D2;
  for (size_t i = 0; i < D1; ++i) {
    for (size_t j = 0; j < D2; ++j) {
      for (size_t k = 0; k < D3; ++k) {
        arr[stride_D1 * i +
            stride_D2 * j +
            stride_D3 * k] = frand(0.0, 1.0);
      }
    }
  }
}

void init_4d(
    float *arr,
    size_t D1, size_t D2, size_t D3, size_t D4) {
  size_t stride_D4 = 1;
  size_t stride_D3 = stride_D4 * D4;
  size_t stride_D2 = stride_D3 * D3;
  size_t stride_D1 = stride_D2 * D2;
  for (size_t i = 0; i < D1; ++i) {
    for (size_t j = 0; j < D2; ++j) {
      for (size_t k = 0; k < D3; ++k) {
        for (size_t l = 0; l < D4; ++l) {
        arr[stride_D1 * i +
            stride_D2 * j +
            stride_D3 * k +
            stride_D4 * l] = frand(0.0, 1.0);
        }
      }
    }
  }
}

void init_scalar(float *scalar) {
  *scalar = frand(0.0, 1.0);
}

void copy_3d(
    const float *src,
    float *dest,
    size_t D1, size_t D2, size_t D3) {
  size_t stride_D3 = 1;
  size_t stride_D2 = stride_D3 * D3;
  size_t stride_D1 = stride_D2 * D2;
  for (size_t i = 0; i < D1; ++i) {
    for (size_t j = 0; j < D2; ++j) {
      for (size_t k = 0; k < D3; ++k) {
        size_t offset_i = stride_D1 * i;
        size_t offset_j = stride_D2 * j;
        size_t offset_k = stride_D3 * k;
        dest[offset_i + offset_j + offset_k] = src[offset_i + offset_j + offset_k];
      }
    }
  }
}
