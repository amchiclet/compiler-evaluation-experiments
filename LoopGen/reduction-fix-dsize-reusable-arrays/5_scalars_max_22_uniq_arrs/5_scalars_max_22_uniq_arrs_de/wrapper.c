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
double (*Arr05_ptr);
double (*Arr06_ptr);
double (*Arr08_ptr);
double (*Arr10_ptr);
double (*Arr11_ptr);
double (*Arr12_ptr);
double (*Arr13_ptr);
double (*Arr14_ptr);
double (*Arr17_ptr);
double (*Arr18_ptr);
double (*Arr20_ptr);
double (*Arr22_ptr);

void allocate_arrays() {
  Arr01_ptr = malloc(sizeof(double) * (8388608));
  Arr02_ptr = malloc(sizeof(double) * (8388608));
  Arr03_ptr = malloc(sizeof(double) * (8388608));
  Arr05_ptr = malloc(sizeof(double) * (8388608));
  Arr06_ptr = malloc(sizeof(double) * (8388608));
  Arr08_ptr = malloc(sizeof(double) * (8388608));
  Arr10_ptr = malloc(sizeof(double) * (8388608));
  Arr11_ptr = malloc(sizeof(double) * (8388608));
  Arr12_ptr = malloc(sizeof(double) * (8388608));
  Arr13_ptr = malloc(sizeof(double) * (8388608));
  Arr14_ptr = malloc(sizeof(double) * (8388608));
  Arr17_ptr = malloc(sizeof(double) * (8388608));
  Arr18_ptr = malloc(sizeof(double) * (8388608));
  Arr20_ptr = malloc(sizeof(double) * (8388608));
  Arr22_ptr = malloc(sizeof(double) * (8388608));
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

void init_arrays(double (*restrict Arr01)[8388608], double (*restrict Arr02)[8388608], double (*restrict Arr03)[8388608], double (*restrict Arr05)[8388608], double (*restrict Arr06)[8388608], double (*restrict Arr08)[8388608], double (*restrict Arr10)[8388608], double (*restrict Arr11)[8388608], double (*restrict Arr12)[8388608], double (*restrict Arr13)[8388608], double (*restrict Arr14)[8388608], double (*restrict Arr17)[8388608], double (*restrict Arr18)[8388608], double (*restrict Arr20)[8388608], double (*restrict Arr22)[8388608]) {
  for (int i0 = 0; i0 <= 381300; i0 += 1) {
    (*Arr01)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 381300; i0 += 1) {
    (*Arr02)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 381300; i0 += 1) {
    (*Arr03)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 381300; i0 += 1) {
    (*Arr05)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 381300; i0 += 1) {
    (*Arr06)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 381300; i0 += 1) {
    (*Arr08)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 381300; i0 += 1) {
    (*Arr10)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 381300; i0 += 1) {
    (*Arr11)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 381300; i0 += 1) {
    (*Arr12)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 381300; i0 += 1) {
    (*Arr13)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 381300; i0 += 1) {
    (*Arr14)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 381300; i0 += 1) {
    (*Arr17)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 381300; i0 += 1) {
    (*Arr18)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 381300; i0 += 1) {
    (*Arr20)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 381300; i0 += 1) {
    (*Arr22)[i0] = drand(0.0, 1.0);
  }
}

void init_array_ptrs() {
  init_arrays((double(*)[8388608])(Arr01_ptr), (double(*)[8388608])(Arr02_ptr), (double(*)[8388608])(Arr03_ptr), (double(*)[8388608])(Arr05_ptr), (double(*)[8388608])(Arr06_ptr), (double(*)[8388608])(Arr08_ptr), (double(*)[8388608])(Arr10_ptr), (double(*)[8388608])(Arr11_ptr), (double(*)[8388608])(Arr12_ptr), (double(*)[8388608])(Arr13_ptr), (double(*)[8388608])(Arr14_ptr), (double(*)[8388608])(Arr17_ptr), (double(*)[8388608])(Arr18_ptr), (double(*)[8388608])(Arr20_ptr), (double(*)[8388608])(Arr22_ptr));
}

void measure_init_();
void measure_start_();
void measure_stop_();

int core(double (*restrict Arr01)[8388608], double (*restrict Arr02)[8388608], double (*restrict Arr03)[8388608], double (*restrict Arr05)[8388608], double (*restrict Arr06)[8388608], double (*restrict Arr08)[8388608], double (*restrict Arr10)[8388608], double (*restrict Arr11)[8388608], double (*restrict Arr12)[8388608], double (*restrict Arr13)[8388608], double (*restrict Arr14)[8388608], double (*restrict Arr17)[8388608], double (*restrict Arr18)[8388608], double (*restrict Arr20)[8388608], double (*restrict Arr22)[8388608]);

void measure(int n_iterations, int inputs[16]) {
  srand(0);
  init_scalars(inputs);
  allocate_arrays();
  init_array_ptrs();

  measure_init_();
  measure_start_();
  for (int i = 0; i < n_iterations; ++i) {
    core((double(*)[8388608])(Arr01_ptr), (double(*)[8388608])(Arr02_ptr), (double(*)[8388608])(Arr03_ptr), (double(*)[8388608])(Arr05_ptr), (double(*)[8388608])(Arr06_ptr), (double(*)[8388608])(Arr08_ptr), (double(*)[8388608])(Arr10_ptr), (double(*)[8388608])(Arr11_ptr), (double(*)[8388608])(Arr12_ptr), (double(*)[8388608])(Arr13_ptr), (double(*)[8388608])(Arr14_ptr), (double(*)[8388608])(Arr17_ptr), (double(*)[8388608])(Arr18_ptr), (double(*)[8388608])(Arr20_ptr), (double(*)[8388608])(Arr22_ptr));
  }
  measure_stop_();
}
