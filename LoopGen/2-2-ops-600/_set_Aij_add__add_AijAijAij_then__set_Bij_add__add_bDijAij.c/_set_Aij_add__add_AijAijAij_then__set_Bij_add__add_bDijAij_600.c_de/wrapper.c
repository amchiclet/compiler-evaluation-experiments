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

double (*A_ptr)[600][600];
double (*B_ptr)[600][600];
double (*C_ptr)[1][1];
double (*D_ptr)[600][600];
double a;
double b;
int n;

void allocate_heap_vars() {
  A_ptr = malloc(sizeof(double) * 600 * 600);
  B_ptr = malloc(sizeof(double) * 600 * 600);
  C_ptr = malloc(sizeof(double) * 1 * 1);
  D_ptr = malloc(sizeof(double) * 600 * 600);
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
  for (int i0 = 0; i0 <= 599; ++i0) {
    for (int i1 = 0; i1 <= 599; ++i1) {
      (*A_ptr)[i0][i1] = drand(0.0, 1.0);
    }
  }
  for (int i0 = 0; i0 <= 599; ++i0) {
    for (int i1 = 0; i1 <= 599; ++i1) {
      (*B_ptr)[i0][i1] = drand(0.0, 1.0);
    }
  }
  for (int i0 = 0; i0 <= 0; ++i0) {
    for (int i1 = 0; i1 <= 0; ++i1) {
      (*C_ptr)[i0][i1] = drand(0.0, 1.0);
    }
  }
  for (int i0 = 0; i0 <= 599; ++i0) {
    for (int i1 = 0; i1 <= 599; ++i1) {
      (*D_ptr)[i0][i1] = drand(0.0, 1.0);
    }
  }
  a = drand(0.0, 1.0);
  b = drand(0.0, 1.0);
  n = irand(599, 599);
}

void measure_init_();
void measure_start_();
void measure_stop_();

int core(double A[restrict 600][600], double B[restrict 600][600], double C[restrict 1][1], double D[restrict 600][600]);

void measure(int n_iterations) {
  allocate_heap_vars();
  init();
  measure_init_();
  measure_start_();
  for (int i = 0; i < n_iterations; ++i) {
    core(*A_ptr, *B_ptr, *C_ptr, *D_ptr);
  }
  measure_stop_();
}
