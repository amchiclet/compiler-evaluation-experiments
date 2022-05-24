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
int size;
double (*Arr01_ptr);
double (*Arr02_ptr);
double (*Arr04_ptr);
double (*Arr05_ptr);
double (*Arr11_ptr);
double (*Arr12_ptr);
double (*Arr13_ptr);
double (*Arr14_ptr);
double (*Arr15_ptr);
double (*Arr16_ptr);
double (*Arr18_ptr);

void allocate_arrays() {
  Arr01_ptr = malloc(sizeof(double) * (8388608));
  Arr02_ptr = malloc(sizeof(double) * (8388608));
  Arr04_ptr = malloc(sizeof(double) * (8388608));
  Arr05_ptr = malloc(sizeof(double) * (8388608));
  Arr11_ptr = malloc(sizeof(double) * (8388608));
  Arr12_ptr = malloc(sizeof(double) * (8388608));
  Arr13_ptr = malloc(sizeof(double) * (8388608));
  Arr14_ptr = malloc(sizeof(double) * (8388608));
  Arr15_ptr = malloc(sizeof(double) * (8388608));
  Arr16_ptr = malloc(sizeof(double) * (8388608));
  Arr18_ptr = malloc(sizeof(double) * (8388608));
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
  size = inputs[0];
}

void init_arrays(double (*restrict Arr01)[8388608], double (*restrict Arr02)[8388608], double (*restrict Arr04)[8388608], double (*restrict Arr05)[8388608], double (*restrict Arr11)[8388608], double (*restrict Arr12)[8388608], double (*restrict Arr13)[8388608], double (*restrict Arr14)[8388608], double (*restrict Arr15)[8388608], double (*restrict Arr16)[8388608], double (*restrict Arr18)[8388608]) {
  for (int i0 = 0; i0 <= 441505; i0 += 1) {
    (*Arr01)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 441505; i0 += 1) {
    (*Arr02)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 441505; i0 += 1) {
    (*Arr04)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 441505; i0 += 1) {
    (*Arr05)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 441505; i0 += 1) {
    (*Arr11)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 441505; i0 += 1) {
    (*Arr12)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 441505; i0 += 1) {
    (*Arr13)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 441505; i0 += 1) {
    (*Arr14)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 441505; i0 += 1) {
    (*Arr15)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 441505; i0 += 1) {
    (*Arr16)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 441505; i0 += 1) {
    (*Arr18)[i0] = drand(0.0, 1.0);
  }
}

void init_array_ptrs() {
  init_arrays((double(*)[8388608])(Arr01_ptr), (double(*)[8388608])(Arr02_ptr), (double(*)[8388608])(Arr04_ptr), (double(*)[8388608])(Arr05_ptr), (double(*)[8388608])(Arr11_ptr), (double(*)[8388608])(Arr12_ptr), (double(*)[8388608])(Arr13_ptr), (double(*)[8388608])(Arr14_ptr), (double(*)[8388608])(Arr15_ptr), (double(*)[8388608])(Arr16_ptr), (double(*)[8388608])(Arr18_ptr));
}

void measure_init_();
void measure_start_();
void measure_stop_();

int core(double (*restrict Arr01)[8388608], double (*restrict Arr02)[8388608], double (*restrict Arr04)[8388608], double (*restrict Arr05)[8388608], double (*restrict Arr11)[8388608], double (*restrict Arr12)[8388608], double (*restrict Arr13)[8388608], double (*restrict Arr14)[8388608], double (*restrict Arr15)[8388608], double (*restrict Arr16)[8388608], double (*restrict Arr18)[8388608]);

void measure(int n_iterations, int inputs[16]) {
  srand(0);
  init_scalars(inputs);
  allocate_arrays();
  init_array_ptrs();

  measure_init_();
  measure_start_();
  for (int i = 0; i < n_iterations; ++i) {
    core((double(*)[8388608])(Arr01_ptr), (double(*)[8388608])(Arr02_ptr), (double(*)[8388608])(Arr04_ptr), (double(*)[8388608])(Arr05_ptr), (double(*)[8388608])(Arr11_ptr), (double(*)[8388608])(Arr12_ptr), (double(*)[8388608])(Arr13_ptr), (double(*)[8388608])(Arr14_ptr), (double(*)[8388608])(Arr15_ptr), (double(*)[8388608])(Arr16_ptr), (double(*)[8388608])(Arr18_ptr));
  }
  measure_stop_();
}
