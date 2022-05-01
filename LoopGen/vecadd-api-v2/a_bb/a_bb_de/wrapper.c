#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <string.h>

int N;
int (*a_ptr);
int (*b_ptr);

void allocate_arrays() {
  a_ptr = malloc(sizeof(int) * (N));
  b_ptr = malloc(sizeof(int) * (N));
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

void init_scalars(int inputs[16]) {
  N = inputs[0];
}

void init_arrays(int (*restrict a)[N], int (*restrict b)[N]) {
  for (int i0 = 0; i0 <= N - 1; i0 += 1) {
    (*a)[i0] = irand(0, 10);
  }
  for (int i0 = 0; i0 <= N - 1; i0 += 1) {
    (*b)[i0] = irand(0, 10);
  }
}

void init_array_ptrs() {
  init_arrays((int(*)[N])(a_ptr), (int(*)[N])(b_ptr));
}

void measure_init_();
void measure_start_();
void measure_stop_();

int core(int (*restrict a)[N], int (*restrict b)[N]);

void measure(int n_iterations, int inputs[16]) {
  srand(0);
  init_scalars(inputs);
  allocate_arrays();
  init_array_ptrs();

  measure_init_();
  measure_start_();
  for (int i = 0; i < n_iterations; ++i) {
    core((int(*)[N])(a_ptr), (int(*)[N])(b_ptr));
  }
  measure_stop_();
}
