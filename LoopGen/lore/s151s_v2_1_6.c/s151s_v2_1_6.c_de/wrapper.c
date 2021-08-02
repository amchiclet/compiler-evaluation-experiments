#include <x86intrin.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <string.h>

int m;
double (*a_ptr);
double (*b_ptr);
double (*e_ptr);

void allocate_arrays() {
  a_ptr = malloc(sizeof(double) * (2) * (32000));
  b_ptr = malloc(sizeof(double) * (2) * (32000));
  e_ptr = malloc(sizeof(double) * (2) * (6) * (32000));
}

float frand(float min, float max) {
  float scale = rand() / (float) RAND_MAX;
  return min + scale * (max - min);
}

int irand(int min, int max) {
  return min + (rand() % (max - min + 1));
}

double drand(double min, double max) {
  double scale = rand() / (double) RAND_MAX;
  return min + scale * (max - min);
}

void init_scalars(int n_elements) {
  m = 1;
}

void init_arrays(double a[restrict 2][32000], double b[restrict 2][32000], double e[restrict 2][6][32000]) {
  for (int i0 = 0; i0 <= 1; ++i0) {
    for (int i1 = 0; i1 <= 31999; ++i1) {
      a[i0][i1] = drand(0.0, 1.0);
    }
  }
  for (int i0 = 0; i0 <= 1; ++i0) {
    for (int i1 = 0; i1 <= 31998; ++i1) {
      b[i0][i1] = drand(0.0, 1.0);
    }
  }
  for (int i0 = 0; i0 <= 1; ++i0) {
    for (int i1 = 0; i1 <= 5; ++i1) {
      for (int i2 = 0; i2 <= 31998; ++i2) {
        e[i0][i1][i2] = drand(0.0, 1.0);
      }
    }
  }
}

void init_array_ptrs() {
  init_arrays(*(double(*)[2][32000])(a_ptr), *(double(*)[2][32000])(b_ptr), *(double(*)[2][6][32000])(e_ptr));
}

void measure_init_();
void measure_start_();
void measure_stop_();

int core(double a[restrict 2][32000], double b[restrict 2][32000], double e[restrict 2][6][32000]);

void measure(int n_iterations, int n_elements) {
  srand(0);
  init_scalars(n_elements);
  allocate_arrays();
  init_array_ptrs();

  measure_init_();
  measure_start_();
  for (int i = 0; i < n_iterations; ++i) {
    core(*(double(*)[2][32000])(a_ptr), *(double(*)[2][32000])(b_ptr), *(double(*)[2][6][32000])(e_ptr));
  }
  measure_stop_();
}
