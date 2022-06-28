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
double (*Arr05_ptr);
double (*Arr06_ptr);
double (*Arr07_ptr);

void allocate_arrays() {
  Arr01_ptr = malloc(sizeof(double) * (1198373));
  Arr02_ptr = malloc(sizeof(double) * (1198373));
  Arr03_ptr = malloc(sizeof(double) * (1198373));
  Arr04_ptr = malloc(sizeof(double) * (1198373));
  Arr05_ptr = malloc(sizeof(double) * (1198373));
  Arr06_ptr = malloc(sizeof(double) * (1198373));
  Arr07_ptr = malloc(sizeof(double) * (1198373));
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
  scalar1 = drand(0.0, 1.0);
  scalar2 = drand(0.0, 1.0);
  scalar3 = drand(0.0, 1.0);
  scalar4 = drand(0.0, 1.0);
  scalar5 = drand(0.0, 1.0);
  size = inputs[0];
}

void init_arrays(double (*restrict Arr01)[1198373], double (*restrict Arr02)[1198373], double (*restrict Arr03)[1198373], double (*restrict Arr04)[1198373], double (*restrict Arr05)[1198373], double (*restrict Arr06)[1198373], double (*restrict Arr07)[1198373]) {
  for (int i0 = 0; i0 <= 1198372; i0 += 1) {
    (*Arr01)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 1198372; i0 += 1) {
    (*Arr02)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 1198372; i0 += 1) {
    (*Arr03)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 1198372; i0 += 1) {
    (*Arr04)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 1198372; i0 += 1) {
    (*Arr05)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 1198372; i0 += 1) {
    (*Arr06)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 1198372; i0 += 1) {
    (*Arr07)[i0] = drand(0.0, 1.0);
  }
}

void init_array_ptrs() {
  init_arrays((double(*)[1198373])(Arr01_ptr), (double(*)[1198373])(Arr02_ptr), (double(*)[1198373])(Arr03_ptr), (double(*)[1198373])(Arr04_ptr), (double(*)[1198373])(Arr05_ptr), (double(*)[1198373])(Arr06_ptr), (double(*)[1198373])(Arr07_ptr));
}

void measure_init_();
void measure_start_();
void measure_stop_();

int core(double (*restrict Arr01)[1198373], double (*restrict Arr02)[1198373], double (*restrict Arr03)[1198373], double (*restrict Arr04)[1198373], double (*restrict Arr05)[1198373], double (*restrict Arr06)[1198373], double (*restrict Arr07)[1198373]);

void measure(int n_iterations, int inputs[16]) {
  srand(0);
  init_scalars(inputs);
  allocate_arrays();
  init_array_ptrs();

  measure_init_();
  measure_start_();
  for (int i = 0; i < n_iterations; ++i) {
    core((double(*)[1198373])(Arr01_ptr), (double(*)[1198373])(Arr02_ptr), (double(*)[1198373])(Arr03_ptr), (double(*)[1198373])(Arr04_ptr), (double(*)[1198373])(Arr05_ptr), (double(*)[1198373])(Arr06_ptr), (double(*)[1198373])(Arr07_ptr));
  }
  measure_stop_();
}
