#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <string.h>

int scalar1;
int scalar2;
int scalar3;
int size;
double (*Arr01_ptr);
double (*Arr02_ptr);
double (*Arr03_ptr);
double (*Arr04_ptr);
double (*Arr05_ptr);
double (*Arr06_ptr);
double (*Arr07_ptr);
double (*Arr08_ptr);
double (*Arr09_ptr);
double (*Arr10_ptr);
double (*Arr11_ptr);
double (*Arr12_ptr);
double (*Arr13_ptr);
double (*Arr14_ptr);

void allocate_arrays() {
  Arr01_ptr = malloc(sizeof(double) * (32000));
  Arr02_ptr = malloc(sizeof(double) * (32000));
  Arr03_ptr = malloc(sizeof(double) * (32000));
  Arr04_ptr = malloc(sizeof(double) * (32000));
  Arr05_ptr = malloc(sizeof(double) * (32000));
  Arr06_ptr = malloc(sizeof(double) * (32000));
  Arr07_ptr = malloc(sizeof(double) * (32000));
  Arr08_ptr = malloc(sizeof(double) * (32000));
  Arr09_ptr = malloc(sizeof(double) * (32000));
  Arr10_ptr = malloc(sizeof(double) * (32000));
  Arr11_ptr = malloc(sizeof(double) * (32000));
  Arr12_ptr = malloc(sizeof(double) * (32000));
  Arr13_ptr = malloc(sizeof(double) * (32000));
  Arr14_ptr = malloc(sizeof(double) * (32000));
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
  scalar1 = irand(0, 10);
  scalar2 = irand(0, 10);
  scalar3 = irand(0, 10);
  size = 32000;
}

void init_arrays(double (*restrict Arr01)[32000], double (*restrict Arr02)[32000], double (*restrict Arr03)[32000], double (*restrict Arr04)[32000], double (*restrict Arr05)[32000], double (*restrict Arr06)[32000], double (*restrict Arr07)[32000], double (*restrict Arr08)[32000], double (*restrict Arr09)[32000], double (*restrict Arr10)[32000], double (*restrict Arr11)[32000], double (*restrict Arr12)[32000], double (*restrict Arr13)[32000], double (*restrict Arr14)[32000]) {
  for (int i0 = 0; i0 <= 31999; i0 += 1) {
    (*Arr01)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 31999; i0 += 1) {
    (*Arr02)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 31999; i0 += 1) {
    (*Arr03)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 31999; i0 += 1) {
    (*Arr04)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 31999; i0 += 1) {
    (*Arr05)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 31999; i0 += 1) {
    (*Arr06)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 31999; i0 += 1) {
    (*Arr07)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 31999; i0 += 1) {
    (*Arr08)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 31999; i0 += 1) {
    (*Arr09)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 31999; i0 += 1) {
    (*Arr10)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 31999; i0 += 1) {
    (*Arr11)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 31999; i0 += 1) {
    (*Arr12)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 31999; i0 += 1) {
    (*Arr13)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 31999; i0 += 1) {
    (*Arr14)[i0] = drand(0.0, 1.0);
  }
}

void init_array_ptrs() {
  init_arrays((double(*)[32000])(Arr01_ptr), (double(*)[32000])(Arr02_ptr), (double(*)[32000])(Arr03_ptr), (double(*)[32000])(Arr04_ptr), (double(*)[32000])(Arr05_ptr), (double(*)[32000])(Arr06_ptr), (double(*)[32000])(Arr07_ptr), (double(*)[32000])(Arr08_ptr), (double(*)[32000])(Arr09_ptr), (double(*)[32000])(Arr10_ptr), (double(*)[32000])(Arr11_ptr), (double(*)[32000])(Arr12_ptr), (double(*)[32000])(Arr13_ptr), (double(*)[32000])(Arr14_ptr));
}

void measure_init_();
void measure_start_();
void measure_stop_();

int core(double (*restrict Arr01)[32000], double (*restrict Arr02)[32000], double (*restrict Arr03)[32000], double (*restrict Arr04)[32000], double (*restrict Arr05)[32000], double (*restrict Arr06)[32000], double (*restrict Arr07)[32000], double (*restrict Arr08)[32000], double (*restrict Arr09)[32000], double (*restrict Arr10)[32000], double (*restrict Arr11)[32000], double (*restrict Arr12)[32000], double (*restrict Arr13)[32000], double (*restrict Arr14)[32000]);

void measure(int n_iterations, int inputs[16]) {
  srand(0);
  init_scalars(inputs);
  allocate_arrays();
  init_array_ptrs();

  measure_init_();
  measure_start_();
  for (int i = 0; i < n_iterations; ++i) {
    core((double(*)[32000])(Arr01_ptr), (double(*)[32000])(Arr02_ptr), (double(*)[32000])(Arr03_ptr), (double(*)[32000])(Arr04_ptr), (double(*)[32000])(Arr05_ptr), (double(*)[32000])(Arr06_ptr), (double(*)[32000])(Arr07_ptr), (double(*)[32000])(Arr08_ptr), (double(*)[32000])(Arr09_ptr), (double(*)[32000])(Arr10_ptr), (double(*)[32000])(Arr11_ptr), (double(*)[32000])(Arr12_ptr), (double(*)[32000])(Arr13_ptr), (double(*)[32000])(Arr14_ptr));
  }
  measure_stop_();
}
