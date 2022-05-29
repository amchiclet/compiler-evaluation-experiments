#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <string.h>

int n_unique_arrs;
double scalar1;
double scalar2;
double scalar3;
double scalar4;
double scalar5;
int size;
double (*Arr01_ptr);
double (*Arr02_ptr);
double (*Arr03_ptr);
double (*Arr04_ptr);

void allocate_arrays() {
  Arr01_ptr = malloc(sizeof(double) * (2097152));
  Arr02_ptr = malloc(sizeof(double) * (2097152));
  Arr03_ptr = malloc(sizeof(double) * (2097152));
  Arr04_ptr = malloc(sizeof(double) * (2097152));
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
  n_unique_arrs = inputs[1];
  scalar1 = drand(0.0, 1.0);
  scalar2 = drand(0.0, 1.0);
  scalar3 = drand(0.0, 1.0);
  scalar4 = drand(0.0, 1.0);
  scalar5 = drand(0.0, 1.0);
  size = inputs[0];
}

void init_arrays(double (*restrict Arr01)[2097152], double (*restrict Arr02)[2097152], double (*restrict Arr03)[2097152], double (*restrict Arr04)[2097152]) {
  for (int i0 = 0; i0 <= 2097151; i0 += 1) {
    (*Arr01)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 2097151; i0 += 1) {
    (*Arr02)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 2097151; i0 += 1) {
    (*Arr03)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 2097151; i0 += 1) {
    (*Arr04)[i0] = drand(0.0, 1.0);
  }
}

void init_array_ptrs() {
  init_arrays((double(*)[2097152])(Arr01_ptr), (double(*)[2097152])(Arr02_ptr), (double(*)[2097152])(Arr03_ptr), (double(*)[2097152])(Arr04_ptr));
}

void measure_init_();
void measure_start_();
void measure_stop_();

int core(double (*restrict Arr01)[2097152], double (*restrict Arr02)[2097152], double (*restrict Arr03)[2097152], double (*restrict Arr04)[2097152]);

void measure(int n_iterations, int inputs[16]) {
  srand(0);
  init_scalars(inputs);
  allocate_arrays();
  init_array_ptrs();

  measure_init_();
  measure_start_();
  for (int i = 0; i < n_iterations; ++i) {
    core((double(*)[2097152])(Arr01_ptr), (double(*)[2097152])(Arr02_ptr), (double(*)[2097152])(Arr03_ptr), (double(*)[2097152])(Arr04_ptr));
  }
  measure_stop_();
}