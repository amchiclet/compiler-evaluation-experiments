#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <string.h>

int n_arrs;
int size;
double (*A_ptr);
double (*B_ptr);
double (*C_ptr);
double (*D_ptr);

void allocate_arrays() {
  A_ptr = malloc(sizeof(double) * (2097152));
  B_ptr = malloc(sizeof(double) * (2097152));
  C_ptr = malloc(sizeof(double) * (2097152));
  D_ptr = malloc(sizeof(double) * (2097152));
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
  n_arrs = inputs[1];
  size = inputs[0];
}

void init_arrays(double (*restrict A)[2097152], double (*restrict B)[2097152], double (*restrict C)[2097152], double (*restrict D)[2097152]) {
  for (int i0 = 0; i0 <= 2097151; i0 += 1) {
    (*A)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 2097151; i0 += 1) {
    (*B)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 2097151; i0 += 1) {
    (*C)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 2097151; i0 += 1) {
    (*D)[i0] = drand(0.0, 1.0);
  }
}

void init_array_ptrs() {
  init_arrays((double(*)[2097152])(A_ptr), (double(*)[2097152])(B_ptr), (double(*)[2097152])(C_ptr), (double(*)[2097152])(D_ptr));
}

void measure_init_();
void measure_start_();
void measure_stop_();

int core(double (*restrict A)[2097152], double (*restrict B)[2097152], double (*restrict C)[2097152], double (*restrict D)[2097152]);

void measure(int n_iterations, int inputs[16]) {
  srand(0);
  init_scalars(inputs);
  allocate_arrays();
  init_array_ptrs();

  measure_init_();
  measure_start_();
  for (int i = 0; i < n_iterations; ++i) {
    core((double(*)[2097152])(A_ptr), (double(*)[2097152])(B_ptr), (double(*)[2097152])(C_ptr), (double(*)[2097152])(D_ptr));
  }
  measure_stop_();
}
