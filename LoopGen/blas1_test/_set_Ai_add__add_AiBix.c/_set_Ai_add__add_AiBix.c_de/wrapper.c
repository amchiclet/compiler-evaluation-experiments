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

int n;
double (*A_ptr);
double (*B_ptr);

void allocate_arrays() {
  A_ptr = malloc(sizeof(double) * (n));
  B_ptr = malloc(sizeof(double) * (n));
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
  n = n_elements;
}

void init_arrays(double A[restrict n], double B[restrict n]) {
  for (int i0 = 0; i0 <= 999999; ++i0) {
    A[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 999999; ++i0) {
    B[i0] = drand(0.0, 1.0);
  }
}

void init_array_ptrs() {
  init_arrays(*(double(*)[n])(A_ptr), *(double(*)[n])(B_ptr));
}

void measure_init_();
void measure_start_();
void measure_stop_();

int core(double A[restrict n], double B[restrict n]);

void measure(int n_iterations, int n_elements) {
  srand(0);
  init_scalars(n_elements);
  allocate_arrays();
  init_array_ptrs();

  measure_init_();
  measure_start_();
  for (int i = 0; i < n_iterations; ++i) {
    core(*(double(*)[n])(A_ptr), *(double(*)[n])(B_ptr));
  }
  measure_stop_();
}
