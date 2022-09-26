#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <string.h>

int M;
int n_arrs;
int size;
double (*a_ptr);
double (*b_ptr);
double (*c_ptr);
double (*d_ptr);

void allocate_arrays() {
  a_ptr = malloc(sizeof(double) * (10000) * (3));
  b_ptr = malloc(sizeof(double) * (3) * (80));
  c_ptr = malloc(sizeof(double) * (10000) * (80));
  d_ptr = malloc(sizeof(double) * (10000) * (80) * (3));
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
  M = (inputs[0] - 80*3) / (80+3+80*3) /* n=80, k=3*/;
  n_arrs = inputs[1];
  size = inputs[0];
}

void init_arrays(double (*restrict a)[10000][3], double (*restrict b)[3][80], double (*restrict c)[10000][80], double (*restrict d)[10000][80][3]) {
  for (int i0 = 0; i0 <= 9999; i0 += 1) {
    for (int i1 = 0; i1 <= 2; i1 += 1) {
      (*a)[i0][i1] = drand(0.0, 1.0);
    }
  }
  for (int i0 = 0; i0 <= 2; i0 += 1) {
    for (int i1 = 0; i1 <= 79; i1 += 1) {
      (*b)[i0][i1] = drand(0.0, 1.0);
    }
  }
  for (int i0 = 0; i0 <= 9999; i0 += 1) {
    for (int i1 = 0; i1 <= 79; i1 += 1) {
      (*c)[i0][i1] = drand(0.0, 1.0);
    }
  }
  for (int i0 = 0; i0 <= 9999; i0 += 1) {
    for (int i1 = 0; i1 <= 79; i1 += 1) {
      for (int i2 = 0; i2 <= 2; i2 += 1) {
        (*d)[i0][i1][i2] = drand(0.5, 2.0);
      }
    }
  }
}

void init_array_ptrs() {
  init_arrays((double(*)[10000][3])(a_ptr), (double(*)[3][80])(b_ptr), (double(*)[10000][80])(c_ptr), (double(*)[10000][80][3])(d_ptr));
}

void measure_init_();
void measure_start_();
void measure_stop_();

int core(double (*restrict a)[10000][3], double (*restrict b)[3][80], double (*restrict c)[10000][80], double (*restrict d)[10000][80][3]);

void measure(int n_iterations, int inputs[16]) {
  srand(0);
  init_scalars(inputs);
  allocate_arrays();
  init_array_ptrs();

  measure_init_();
  measure_start_();
  for (int i = 0; i < n_iterations; ++i) {
    core((double(*)[10000][3])(a_ptr), (double(*)[3][80])(b_ptr), (double(*)[10000][80])(c_ptr), (double(*)[10000][80][3])(d_ptr));
  }
  measure_stop_();
}
