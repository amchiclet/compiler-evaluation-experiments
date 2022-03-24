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


void allocate_arrays() {

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

void init_arrays() {

}

void init_array_ptrs() {
  init_arrays();
}

void measure_init_();
void measure_start_();
void measure_stop_();

int core();

void measure(int n_iterations, int inputs[16]) {
  srand(0);
  init_scalars(inputs);
  allocate_arrays();
  init_array_ptrs();

  measure_init_();
  measure_start_();
  for (int i = 0; i < n_iterations; ++i) {
    core();
  }
  measure_stop_();
}
