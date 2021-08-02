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

void allocate_arrays() {
  a_ptr = malloc(sizeof(double) * (32000));
  b_ptr = malloc(sizeof(double) * (32000));
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

void init_arrays(double a[restrict 32000], double b[restrict 32000]) {
  for (int i0 = 0; i0 <= 31999; ++i0) {
    a[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 31998; ++i0) {
    b[i0] = drand(0.0, 1.0);
  }
}

void init_array_ptrs() {
  init_arrays(*(double(*)[32000])(a_ptr), *(double(*)[32000])(b_ptr));
}

void measure_init_();
void measure_start_();
void measure_stop_();

int core(double a[restrict 32000], double b[restrict 32000]);

void measure(int n_iterations, int n_elements) {
  srand(0);
  init_scalars(n_elements);
  allocate_arrays();
  init_array_ptrs();

  measure_init_();
  measure_start_();
  for (int i = 0; i < n_iterations; ++i) {
    core(*(double(*)[32000])(a_ptr), *(double(*)[32000])(b_ptr));
  }
  measure_stop_();
}
