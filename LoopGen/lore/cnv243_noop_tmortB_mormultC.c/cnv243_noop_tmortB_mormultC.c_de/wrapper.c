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

int nmor;
double (*A_ptr);
double (*B_ptr);
double (*C_ptr);
double (*mormult_ptr);
double (*tmort_ptr);

void allocate_arrays() {
  A_ptr = malloc(sizeof(double) * (1));
  B_ptr = malloc(sizeof(double) * (92700));
  C_ptr = malloc(sizeof(double) * (92700));
  mormult_ptr = malloc(sizeof(double) * (92700));
  tmort_ptr = malloc(sizeof(double) * (92700));
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
  nmor = 92700;
}

void init_arrays(double A[restrict 1], double B[restrict 92700], double C[restrict 92700], double mormult[restrict 92700], double tmort[restrict 92700]) {
  for (int i0 = 0; i0 <= 0; ++i0) {
    A[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 92699; ++i0) {
    B[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 92699; ++i0) {
    C[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 92699; ++i0) {
    mormult[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 92699; ++i0) {
    tmort[i0] = drand(0.0, 1.0);
  }
}

void init_array_ptrs() {
  init_arrays(*(double(*)[1])(A_ptr), *(double(*)[92700])(B_ptr), *(double(*)[92700])(C_ptr), *(double(*)[92700])(mormult_ptr), *(double(*)[92700])(tmort_ptr));
}

void measure_init_();
void measure_start_();
void measure_stop_();

int core(double A[restrict 1], double B[restrict 92700], double C[restrict 92700], double mormult[restrict 92700], double tmort[restrict 92700]);

void measure(int n_iterations, int n_elements) {
  srand(0);
  init_scalars(n_elements);
  allocate_arrays();
  init_array_ptrs();

  measure_init_();
  measure_start_();
  for (int i = 0; i < n_iterations; ++i) {
    core(*(double(*)[1])(A_ptr), *(double(*)[92700])(B_ptr), *(double(*)[92700])(C_ptr), *(double(*)[92700])(mormult_ptr), *(double(*)[92700])(tmort_ptr));
  }
  measure_stop_();
}
