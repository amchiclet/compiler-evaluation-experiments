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

int nj;
int nl;
int nm;
double (*C_ptr);
double (*D_ptr);
double (*F_ptr);

void allocate_arrays() {
  C_ptr = malloc(sizeof(double) * (900) * (1200));
  D_ptr = malloc(sizeof(double) * (1200) * (1100));
  F_ptr = malloc(sizeof(double) * (900) * (1100));
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
  nj = 900;
  nl = 1100;
  nm = 1200;
}

void init_arrays(double C[restrict 900][1200], double D[restrict 1200][1100], double F[restrict 900][1100]) {
  for (int i0 = 0; i0 <= 899; ++i0) {
    for (int i1 = 0; i1 <= 1199; ++i1) {
      C[i0][i1] = drand(0.0, 1.0);
    }
  }
  for (int i0 = 0; i0 <= 1199; ++i0) {
    for (int i1 = 0; i1 <= 1099; ++i1) {
      D[i0][i1] = drand(0.0, 1.0);
    }
  }
  for (int i0 = 0; i0 <= 899; ++i0) {
    for (int i1 = 0; i1 <= 1099; ++i1) {
      F[i0][i1] = drand(0.0, 1.0);
    }
  }
}

void init_array_ptrs() {
  init_arrays(*(double(*)[900][1200])(C_ptr), *(double(*)[1200][1100])(D_ptr), *(double(*)[900][1100])(F_ptr));
}

void measure_init_();
void measure_start_();
void measure_stop_();

int core(double C[restrict 900][1200], double D[restrict 1200][1100], double F[restrict 900][1100]);

void measure(int n_iterations, int n_elements) {
  srand(0);
  init_scalars(n_elements);
  allocate_arrays();
  init_array_ptrs();

  measure_init_();
  measure_start_();
  for (int i = 0; i < n_iterations; ++i) {
    core(*(double(*)[900][1200])(C_ptr), *(double(*)[1200][1100])(D_ptr), *(double(*)[900][1100])(F_ptr));
  }
  measure_stop_();
}
