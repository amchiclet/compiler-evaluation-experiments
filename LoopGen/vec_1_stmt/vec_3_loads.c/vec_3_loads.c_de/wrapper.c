#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <string.h>

int I;
double (*A_ptr);
double (*B1_ptr);
double (*B2_ptr);
double (*B3_ptr);
double (*B4_ptr);
double (*B5_ptr);
double (*B6_ptr);
double (*B7_ptr);
double (*B8_ptr);
double (*B9_ptr);

void allocate_arrays() {
  A_ptr = malloc(sizeof(double) * (32000));
  B1_ptr = malloc(sizeof(double) * (32000));
  B2_ptr = malloc(sizeof(double) * (32000));
  B3_ptr = malloc(sizeof(double) * (32000));
  B4_ptr = malloc(sizeof(double) * (1));
  B5_ptr = malloc(sizeof(double) * (1));
  B6_ptr = malloc(sizeof(double) * (1));
  B7_ptr = malloc(sizeof(double) * (1));
  B8_ptr = malloc(sizeof(double) * (1));
  B9_ptr = malloc(sizeof(double) * (1));
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
  I = 32000;
}

void init_arrays(double A[restrict 32000], double B1[restrict 32000], double B2[restrict 32000], double B3[restrict 32000], double B4[restrict 1], double B5[restrict 1], double B6[restrict 1], double B7[restrict 1], double B8[restrict 1], double B9[restrict 1]) {
  for (int i0 = 0; i0 <= 31999; ++i0) {
    A[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 31999; ++i0) {
    B1[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 31999; ++i0) {
    B2[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 31999; ++i0) {
    B3[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 0; ++i0) {
    B4[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 0; ++i0) {
    B5[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 0; ++i0) {
    B6[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 0; ++i0) {
    B7[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 0; ++i0) {
    B8[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 0; ++i0) {
    B9[i0] = drand(0.0, 1.0);
  }
}

void init_array_ptrs() {
  init_arrays(*(double(*)[32000])(A_ptr), *(double(*)[32000])(B1_ptr), *(double(*)[32000])(B2_ptr), *(double(*)[32000])(B3_ptr), *(double(*)[1])(B4_ptr), *(double(*)[1])(B5_ptr), *(double(*)[1])(B6_ptr), *(double(*)[1])(B7_ptr), *(double(*)[1])(B8_ptr), *(double(*)[1])(B9_ptr));
}

void measure_init_();
void measure_start_();
void measure_stop_();

int core(double A[restrict 32000], double B1[restrict 32000], double B2[restrict 32000], double B3[restrict 32000], double B4[restrict 1], double B5[restrict 1], double B6[restrict 1], double B7[restrict 1], double B8[restrict 1], double B9[restrict 1]);

void measure(int n_iterations, int inputs[16]) {
  srand(0);
  init_scalars(inputs);
  allocate_arrays();
  init_array_ptrs();

  measure_init_();
  measure_start_();
  for (int i = 0; i < n_iterations; ++i) {
    core(*(double(*)[32000])(A_ptr), *(double(*)[32000])(B1_ptr), *(double(*)[32000])(B2_ptr), *(double(*)[32000])(B3_ptr), *(double(*)[1])(B4_ptr), *(double(*)[1])(B5_ptr), *(double(*)[1])(B6_ptr), *(double(*)[1])(B7_ptr), *(double(*)[1])(B8_ptr), *(double(*)[1])(B9_ptr));
  }
  measure_stop_();
}
