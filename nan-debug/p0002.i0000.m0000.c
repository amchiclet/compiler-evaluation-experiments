#include <x86intrin.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <assert.h>
#include <limits.h>
#include <string.h>

unsigned long long core(float A[restrict 35], float B[restrict 61], float C[restrict 43], float D[restrict 53], float E[restrict 58]) {
  struct timespec before, after;
  clock_gettime(CLOCK_MONOTONIC, &before);
  for (int i3 = 11; i3 <= 22; i3+=1) {
    for (int i1 = 13; i1 <= 39; i1+=1) {
      for (int i2 = 14; i2 <= 31; i2+=1) {
          A[1 * i3 - 11] = B[1 * i2 - 11] - 23;
          C[1 * i3 + 11] = C[1 * i2 - 13] + A[1 * i3 - 11];
      }
    }
  }
  for (int i5 = 18; i5 <= 19; i5+=1) {
    for (int i6 = 44; i6 <= 47; i6+=1) {
      for (int i4 = 12; i4 <= 44; i4+=1) {
          D[1 * i4 - 11] = 9 - B[1 * i5 - 11];
          E[1 * i4 + 13] = E[1 * i5 - 11] * 42;
      }
    }
  }
  for (int i6 = 44; i6 <= 47; i6+=1) {
    for (int i4 = 12; i4 <= 44; i4+=1) {
      for (int i2 = 14; i2 <= 31; i2+=1) {
          A[1 * i6 - 13] = A[1 * i4 - 11] * B[1 * i6 - 3];
          C[1 * i2 + 11] = C[1 * i6 - 13] * 42;
      }
    }
  }
  for (int i6 = 44; i6 <= 47; i6+=1) {
    for (int i4 = 12; i4 <= 44; i4+=1) {
      for (int i2 = 14; i2 <= 31; i2+=1) {
          B[1 * i6 + 13] = 9 * E[1 * i2 + 3];
          D[1 * i2 - 11] = D[1 * i4 + 3] - 23;
      }
    }
  }
  for (int i5 = 18; i5 <= 19; i5+=1) {
    for (int i4 = 12; i4 <= 44; i4+=1) {
      for (int i1 = 13; i1 <= 39; i1+=1) {
          E[1 * i4 - 11] = E[1 * i5 + 13] * D[1 * i1 - 13];
          E[1 * i5 - 3] = D[1 * i1 + 13] * 9;
      }
    }
  }
  clock_gettime(CLOCK_MONOTONIC, &after);
  unsigned long long duration = (after.tv_sec - before.tv_sec) * 1e9;
  duration += after.tv_nsec - before.tv_nsec;
  return duration;
}

