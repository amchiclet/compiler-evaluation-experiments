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
int size;
double (*Arr01_ptr);
double (*Arr02_ptr);
double (*Arr03_ptr);
double (*Arr04_ptr);
double (*Arr07_ptr);
double (*Arr09_ptr);
double (*Arr11_ptr);
double (*Arr12_ptr);

void allocate_arrays() {
  Arr01_ptr = malloc(sizeof(double) * (699051));
  Arr02_ptr = malloc(sizeof(double) * (699051));
  Arr03_ptr = malloc(sizeof(double) * (699051));
  Arr04_ptr = malloc(sizeof(double) * (699051));
  Arr07_ptr = malloc(sizeof(double) * (699051));
  Arr09_ptr = malloc(sizeof(double) * (699051));
  Arr11_ptr = malloc(sizeof(double) * (699051));
  Arr12_ptr = malloc(sizeof(double) * (699051));
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
  size = inputs[0];
}

void init_arrays(double (*restrict Arr01)[699051], double (*restrict Arr02)[699051], double (*restrict Arr03)[699051], double (*restrict Arr04)[699051], double (*restrict Arr07)[699051], double (*restrict Arr09)[699051], double (*restrict Arr11)[699051], double (*restrict Arr12)[699051]) {
  for (int i0 = 0; i0 <= 699050; i0 += 1) {
    (*Arr01)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 699050; i0 += 1) {
    (*Arr02)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 699050; i0 += 1) {
    (*Arr03)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 699050; i0 += 1) {
    (*Arr04)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 699050; i0 += 1) {
    (*Arr07)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 699050; i0 += 1) {
    (*Arr09)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 699050; i0 += 1) {
    (*Arr11)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 699050; i0 += 1) {
    (*Arr12)[i0] = drand(0.0, 1.0);
  }
}

void init_array_ptrs() {
  init_arrays((double(*)[699051])(Arr01_ptr), (double(*)[699051])(Arr02_ptr), (double(*)[699051])(Arr03_ptr), (double(*)[699051])(Arr04_ptr), (double(*)[699051])(Arr07_ptr), (double(*)[699051])(Arr09_ptr), (double(*)[699051])(Arr11_ptr), (double(*)[699051])(Arr12_ptr));
}

void measure_init_();
void measure_start_();
void measure_stop_();

int core(double (*restrict Arr01)[699051], double (*restrict Arr02)[699051], double (*restrict Arr03)[699051], double (*restrict Arr04)[699051], double (*restrict Arr07)[699051], double (*restrict Arr09)[699051], double (*restrict Arr11)[699051], double (*restrict Arr12)[699051]);

void measure(int n_iterations, int inputs[16]) {
  srand(0);
  init_scalars(inputs);
  allocate_arrays();
  init_array_ptrs();

  measure_init_();
  measure_start_();
  for (int i = 0; i < n_iterations; ++i) {
    core((double(*)[699051])(Arr01_ptr), (double(*)[699051])(Arr02_ptr), (double(*)[699051])(Arr03_ptr), (double(*)[699051])(Arr04_ptr), (double(*)[699051])(Arr07_ptr), (double(*)[699051])(Arr09_ptr), (double(*)[699051])(Arr11_ptr), (double(*)[699051])(Arr12_ptr));
  }
  measure_stop_();
}
