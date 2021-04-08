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

double (*A_ptr)[1][1];
double (*B_ptr)[850][850];
double (*C_ptr)[850][850];
double (*D_ptr)[1][1];
double (*E_ptr)[850][850];
double a;
double b;
int n;

void allocate_heap_vars() {
  A_ptr = malloc(sizeof(double) * 1 * 1);
  B_ptr = malloc(sizeof(double) * 850 * 850);
  C_ptr = malloc(sizeof(double) * 850 * 850);
  D_ptr = malloc(sizeof(double) * 1 * 1);
  E_ptr = malloc(sizeof(double) * 850 * 850);
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

void init() {
  srand(0);
  for (int i0 = 0; i0 <= 0; ++i0) {
    for (int i1 = 0; i1 <= 0; ++i1) {
      (*A_ptr)[i0][i1] = drand(0.0, 1.0);
    }
  }
  for (int i0 = 0; i0 <= 849; ++i0) {
    for (int i1 = 0; i1 <= 849; ++i1) {
      (*B_ptr)[i0][i1] = drand(0.0, 1.0);
    }
  }
  for (int i0 = 0; i0 <= 849; ++i0) {
    for (int i1 = 0; i1 <= 849; ++i1) {
      (*C_ptr)[i0][i1] = drand(0.0, 1.0);
    }
  }
  for (int i0 = 0; i0 <= 0; ++i0) {
    for (int i1 = 0; i1 <= 0; ++i1) {
      (*D_ptr)[i0][i1] = drand(0.0, 1.0);
    }
  }
  for (int i0 = 0; i0 <= 849; ++i0) {
    for (int i1 = 0; i1 <= 849; ++i1) {
      (*E_ptr)[i0][i1] = drand(0.0, 1.0);
    }
  }
  a = drand(0.0, 1.0);
  b = drand(0.0, 1.0);
  n = irand(0, 10);
}

void measure_init_();
void measure_start_();
void measure_stop_();

int core(double A[restrict 1][1], double B[restrict 850][850], double C[restrict 850][850], double D[restrict 1][1], double E[restrict 850][850]);

void measure(int n_iterations) {
  allocate_heap_vars();
  init();
  measure_init_();
  measure_start_();
  for (int i = 0; i < n_iterations; ++i) {
    core(*A_ptr, *B_ptr, *C_ptr, *D_ptr, *E_ptr);
  }
  measure_stop_();
}
