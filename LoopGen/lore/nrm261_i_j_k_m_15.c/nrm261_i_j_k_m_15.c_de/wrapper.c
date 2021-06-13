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

double add;
int (*grid_points_ptr);
double (*rhs_ptr);
double (*rms_ptr);

void allocate_arrays() {
  grid_points_ptr = malloc(sizeof(int) * (3));
  rhs_ptr = malloc(sizeof(double) * ((64 / 2) * 2 + 1) * ((64 / 2) * 2 + 1) * ((64 / 2) * 2 + 1) * (15));
  rms_ptr = malloc(sizeof(double) * (15));
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
  add = drand(0.0, 1.0);
}

void init_arrays(int grid_points[restrict 3], double rhs[restrict (64 / 2) * 2 + 1][(64 / 2) * 2 + 1][(64 / 2) * 2 + 1][15], double rms[restrict 15]) {
  for (int i0 = 0; i0 <= 2; ++i0) {
    grid_points[i0] = 66.0;
  }
  for (int i0 = 1; i0 <= ((64 / 2) * 2 + 1) - 1; ++i0) {
    for (int i1 = 1; i1 <= ((64 / 2) * 2 + 1) - 1; ++i1) {
      for (int i2 = 1; i2 <= ((64 / 2) * 2 + 1) - 1; ++i2) {
        for (int i3 = 0; i3 <= 14; ++i3) {
          rhs[i0][i1][i2][i3] = drand(0.0, 1.0);
        }
      }
    }
  }
  for (int i0 = 0; i0 <= 14; ++i0) {
    rms[i0] = drand(0.0, 1.0);
  }
}

void init_array_ptrs() {
  init_arrays(*(int(*)[3])(grid_points_ptr), *(double(*)[(64 / 2) * 2 + 1][(64 / 2) * 2 + 1][(64 / 2) * 2 + 1][15])(rhs_ptr), *(double(*)[15])(rms_ptr));
}

void measure_init_();
void measure_start_();
void measure_stop_();

int core(int grid_points[restrict 3], double rhs[restrict (64 / 2) * 2 + 1][(64 / 2) * 2 + 1][(64 / 2) * 2 + 1][15], double rms[restrict 15]);

void measure(int n_iterations, int n_elements) {
  srand(0);
  init_scalars(n_elements);
  allocate_arrays();
  init_array_ptrs();

  measure_init_();
  measure_start_();
  for (int i = 0; i < n_iterations; ++i) {
    core(*(int(*)[3])(grid_points_ptr), *(double(*)[(64 / 2) * 2 + 1][(64 / 2) * 2 + 1][(64 / 2) * 2 + 1][15])(rhs_ptr), *(double(*)[15])(rms_ptr));
  }
  measure_stop_();
}
