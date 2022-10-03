#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <string.h>

int IFM;
int IMG;
int OFM;
int SH;
int SW;
double (*filter_ptr);
double (*input_ptr);
double (*output_ptr);

void allocate_arrays() {
  filter_ptr = malloc(sizeof(double) * (5) * (5) * (3) * (1));
  input_ptr = malloc(sizeof(double) * (512) * (5) * (11) * (9));
  output_ptr = malloc(sizeof(double) * (512) * (5) * (5) * (5));
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
  IFM = 5;
  IMG = 512;
  OFM = 5;
  SH = 2;
  SW = 2;
}

void init_arrays(double (*restrict filter)[5][5][3][1], double (*restrict input)[512][5][11][9], double (*restrict output)[512][5][5][5]) {
  for (int i0 = 0; i0 <= 4; i0 += 1) {
    for (int i1 = 0; i1 <= 4; i1 += 1) {
      for (int i2 = 0; i2 <= 2; i2 += 1) {
        for (int i3 = 0; i3 <= 0; i3 += 1) {
          (*filter)[i0][i1][i2][i3] = drand(0.0, 1.0);
        }
      }
    }
  }
  for (int i0 = 0; i0 <= 511; i0 += 1) {
    for (int i1 = 0; i1 <= 4; i1 += 1) {
      for (int i2 = 0; i2 <= 10; i2 += 1) {
        for (int i3 = 0; i3 <= 8; i3 += 1) {
          (*input)[i0][i1][i2][i3] = drand(0.0, 1.0);
        }
      }
    }
  }
  for (int i0 = 0; i0 <= 511; i0 += 1) {
    for (int i1 = 0; i1 <= 4; i1 += 1) {
      for (int i2 = 0; i2 <= 4; i2 += 1) {
        for (int i3 = 0; i3 <= 4; i3 += 1) {
          (*output)[i0][i1][i2][i3] = drand(0.0, 1.0);
        }
      }
    }
  }
}

void init_array_ptrs() {
  init_arrays((double(*)[5][5][3][1])(filter_ptr), (double(*)[512][5][11][9])(input_ptr), (double(*)[512][5][5][5])(output_ptr));
}

void measure_init_();
void measure_start_();
void measure_stop_();

int core(double (*restrict filter)[5][5][3][1], double (*restrict input)[512][5][11][9], double (*restrict output)[512][5][5][5]);

void measure(int n_iterations, int inputs[16]) {
  srand(0);
  init_scalars(inputs);
  allocate_arrays();
  init_array_ptrs();

  measure_init_();
  measure_start_();
  for (int i = 0; i < n_iterations; ++i) {
    core((double(*)[5][5][3][1])(filter_ptr), (double(*)[512][5][11][9])(input_ptr), (double(*)[512][5][5][5])(output_ptr));
  }
  measure_stop_();
}
