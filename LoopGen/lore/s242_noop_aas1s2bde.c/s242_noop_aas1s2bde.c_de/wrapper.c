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

double s1;
double s2;
double (*a_ptr);
double (*b_ptr);
double (*c_ptr);
double (*d_ptr);
double (*e_ptr);
double (*f_ptr);
double (*g_ptr);

void allocate_arrays() {
  a_ptr = malloc(sizeof(double) * (32000));
  b_ptr = malloc(sizeof(double) * (32000));
  c_ptr = malloc(sizeof(double) * (32000));
  d_ptr = malloc(sizeof(double) * (32000));
  e_ptr = malloc(sizeof(double) * (32000));
  f_ptr = malloc(sizeof(double) * (32000));
  g_ptr = malloc(sizeof(double) * (32000));
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
  s1 = drand(0.0, 1.0);
  s2 = drand(0.0, 1.0);
}

void init_arrays(double a[restrict 32000], double b[restrict 32000], double c[restrict 32000], double d[restrict 32000], double e[restrict 32000], double f[restrict 32000], double g[restrict 32000]) {
  for (int i0 = 0; i0 <= 31999; ++i0) {
    a[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 1; i0 <= 31999; ++i0) {
    b[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 0; ++i0) {
    c[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 1; i0 <= 31999; ++i0) {
    d[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 1; i0 <= 31999; ++i0) {
    e[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 0; ++i0) {
    f[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 0; ++i0) {
    g[i0] = drand(0.0, 1.0);
  }
}

void init_array_ptrs() {
  init_arrays(*(double(*)[32000])(a_ptr), *(double(*)[32000])(b_ptr), *(double(*)[32000])(c_ptr), *(double(*)[32000])(d_ptr), *(double(*)[32000])(e_ptr), *(double(*)[32000])(f_ptr), *(double(*)[32000])(g_ptr));
}

void measure_init_();
void measure_start_();
void measure_stop_();

int core(double a[restrict 32000], double b[restrict 32000], double c[restrict 32000], double d[restrict 32000], double e[restrict 32000], double f[restrict 32000], double g[restrict 32000]);

void measure(int n_iterations, int n_elements) {
  srand(0);
  init_scalars(n_elements);
  allocate_arrays();
  init_array_ptrs();

  measure_init_();
  measure_start_();
  for (int i = 0; i < n_iterations; ++i) {
    core(*(double(*)[32000])(a_ptr), *(double(*)[32000])(b_ptr), *(double(*)[32000])(c_ptr), *(double(*)[32000])(d_ptr), *(double(*)[32000])(e_ptr), *(double(*)[32000])(f_ptr), *(double(*)[32000])(g_ptr));
  }
  measure_stop_();
}
