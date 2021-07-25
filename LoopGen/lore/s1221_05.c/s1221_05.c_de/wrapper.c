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

int m;
double (*a_ptr);
double (*a10_ptr);
double (*a11_ptr);
double (*a12_ptr);
double (*a13_ptr);
double (*a14_ptr);
double (*a15_ptr);
double (*a16_ptr);
double (*a2_ptr);
double (*a3_ptr);
double (*a4_ptr);
double (*a5_ptr);
double (*a6_ptr);
double (*a7_ptr);
double (*a8_ptr);
double (*a9_ptr);
double (*b_ptr);
double (*b10_ptr);
double (*b11_ptr);
double (*b12_ptr);
double (*b13_ptr);
double (*b14_ptr);
double (*b15_ptr);
double (*b16_ptr);
double (*b2_ptr);
double (*b3_ptr);
double (*b4_ptr);
double (*b5_ptr);
double (*b6_ptr);
double (*b7_ptr);
double (*b8_ptr);
double (*b9_ptr);

void allocate_arrays() {
  a_ptr = malloc(sizeof(double) * (32000));
  a10_ptr = malloc(sizeof(double) * (1));
  a11_ptr = malloc(sizeof(double) * (1));
  a12_ptr = malloc(sizeof(double) * (1));
  a13_ptr = malloc(sizeof(double) * (1));
  a14_ptr = malloc(sizeof(double) * (1));
  a15_ptr = malloc(sizeof(double) * (1));
  a16_ptr = malloc(sizeof(double) * (1));
  a2_ptr = malloc(sizeof(double) * (32000));
  a3_ptr = malloc(sizeof(double) * (32000));
  a4_ptr = malloc(sizeof(double) * (32000));
  a5_ptr = malloc(sizeof(double) * (32000));
  a6_ptr = malloc(sizeof(double) * (1));
  a7_ptr = malloc(sizeof(double) * (1));
  a8_ptr = malloc(sizeof(double) * (1));
  a9_ptr = malloc(sizeof(double) * (1));
  b_ptr = malloc(sizeof(double) * (32000));
  b10_ptr = malloc(sizeof(double) * (1));
  b11_ptr = malloc(sizeof(double) * (1));
  b12_ptr = malloc(sizeof(double) * (1));
  b13_ptr = malloc(sizeof(double) * (1));
  b14_ptr = malloc(sizeof(double) * (1));
  b15_ptr = malloc(sizeof(double) * (1));
  b16_ptr = malloc(sizeof(double) * (1));
  b2_ptr = malloc(sizeof(double) * (32000));
  b3_ptr = malloc(sizeof(double) * (32000));
  b4_ptr = malloc(sizeof(double) * (32000));
  b5_ptr = malloc(sizeof(double) * (32000));
  b6_ptr = malloc(sizeof(double) * (1));
  b7_ptr = malloc(sizeof(double) * (1));
  b8_ptr = malloc(sizeof(double) * (1));
  b9_ptr = malloc(sizeof(double) * (1));
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
  m = irand(0, 10);
}

void init_arrays(double a[restrict 32000], double a10[restrict 1], double a11[restrict 1], double a12[restrict 1], double a13[restrict 1], double a14[restrict 1], double a15[restrict 1], double a16[restrict 1], double a2[restrict 32000], double a3[restrict 32000], double a4[restrict 32000], double a5[restrict 32000], double a6[restrict 1], double a7[restrict 1], double a8[restrict 1], double a9[restrict 1], double b[restrict 32000], double b10[restrict 1], double b11[restrict 1], double b12[restrict 1], double b13[restrict 1], double b14[restrict 1], double b15[restrict 1], double b16[restrict 1], double b2[restrict 32000], double b3[restrict 32000], double b4[restrict 32000], double b5[restrict 32000], double b6[restrict 1], double b7[restrict 1], double b8[restrict 1], double b9[restrict 1]) {
  for (int i0 = 4; i0 <= 31999; ++i0) {
    a[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 0; ++i0) {
    a10[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 0; ++i0) {
    a11[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 0; ++i0) {
    a12[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 0; ++i0) {
    a13[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 0; ++i0) {
    a14[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 0; ++i0) {
    a15[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 0; ++i0) {
    a16[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 4; i0 <= 31999; ++i0) {
    a2[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 4; i0 <= 31999; ++i0) {
    a3[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 4; i0 <= 31999; ++i0) {
    a4[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 4; i0 <= 31999; ++i0) {
    a5[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 0; ++i0) {
    a6[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 0; ++i0) {
    a7[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 0; ++i0) {
    a8[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 0; ++i0) {
    a9[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 31999; ++i0) {
    b[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 0; ++i0) {
    b10[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 0; ++i0) {
    b11[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 0; ++i0) {
    b12[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 0; ++i0) {
    b13[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 0; ++i0) {
    b14[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 0; ++i0) {
    b15[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 0; ++i0) {
    b16[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 31999; ++i0) {
    b2[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 31999; ++i0) {
    b3[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 31999; ++i0) {
    b4[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 31999; ++i0) {
    b5[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 0; ++i0) {
    b6[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 0; ++i0) {
    b7[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 0; ++i0) {
    b8[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 0; ++i0) {
    b9[i0] = drand(0.0, 1.0);
  }
}

void init_array_ptrs() {
  init_arrays(*(double(*)[32000])(a_ptr), *(double(*)[1])(a10_ptr), *(double(*)[1])(a11_ptr), *(double(*)[1])(a12_ptr), *(double(*)[1])(a13_ptr), *(double(*)[1])(a14_ptr), *(double(*)[1])(a15_ptr), *(double(*)[1])(a16_ptr), *(double(*)[32000])(a2_ptr), *(double(*)[32000])(a3_ptr), *(double(*)[32000])(a4_ptr), *(double(*)[32000])(a5_ptr), *(double(*)[1])(a6_ptr), *(double(*)[1])(a7_ptr), *(double(*)[1])(a8_ptr), *(double(*)[1])(a9_ptr), *(double(*)[32000])(b_ptr), *(double(*)[1])(b10_ptr), *(double(*)[1])(b11_ptr), *(double(*)[1])(b12_ptr), *(double(*)[1])(b13_ptr), *(double(*)[1])(b14_ptr), *(double(*)[1])(b15_ptr), *(double(*)[1])(b16_ptr), *(double(*)[32000])(b2_ptr), *(double(*)[32000])(b3_ptr), *(double(*)[32000])(b4_ptr), *(double(*)[32000])(b5_ptr), *(double(*)[1])(b6_ptr), *(double(*)[1])(b7_ptr), *(double(*)[1])(b8_ptr), *(double(*)[1])(b9_ptr));
}

void measure_init_();
void measure_start_();
void measure_stop_();

int core(double a[restrict 32000], double a10[restrict 1], double a11[restrict 1], double a12[restrict 1], double a13[restrict 1], double a14[restrict 1], double a15[restrict 1], double a16[restrict 1], double a2[restrict 32000], double a3[restrict 32000], double a4[restrict 32000], double a5[restrict 32000], double a6[restrict 1], double a7[restrict 1], double a8[restrict 1], double a9[restrict 1], double b[restrict 32000], double b10[restrict 1], double b11[restrict 1], double b12[restrict 1], double b13[restrict 1], double b14[restrict 1], double b15[restrict 1], double b16[restrict 1], double b2[restrict 32000], double b3[restrict 32000], double b4[restrict 32000], double b5[restrict 32000], double b6[restrict 1], double b7[restrict 1], double b8[restrict 1], double b9[restrict 1]);

void measure(int n_iterations, int n_elements) {
  srand(0);
  init_scalars(n_elements);
  allocate_arrays();
  init_array_ptrs();

  measure_init_();
  measure_start_();
  for (int i = 0; i < n_iterations; ++i) {
    core(*(double(*)[32000])(a_ptr), *(double(*)[1])(a10_ptr), *(double(*)[1])(a11_ptr), *(double(*)[1])(a12_ptr), *(double(*)[1])(a13_ptr), *(double(*)[1])(a14_ptr), *(double(*)[1])(a15_ptr), *(double(*)[1])(a16_ptr), *(double(*)[32000])(a2_ptr), *(double(*)[32000])(a3_ptr), *(double(*)[32000])(a4_ptr), *(double(*)[32000])(a5_ptr), *(double(*)[1])(a6_ptr), *(double(*)[1])(a7_ptr), *(double(*)[1])(a8_ptr), *(double(*)[1])(a9_ptr), *(double(*)[32000])(b_ptr), *(double(*)[1])(b10_ptr), *(double(*)[1])(b11_ptr), *(double(*)[1])(b12_ptr), *(double(*)[1])(b13_ptr), *(double(*)[1])(b14_ptr), *(double(*)[1])(b15_ptr), *(double(*)[1])(b16_ptr), *(double(*)[32000])(b2_ptr), *(double(*)[32000])(b3_ptr), *(double(*)[32000])(b4_ptr), *(double(*)[32000])(b5_ptr), *(double(*)[1])(b6_ptr), *(double(*)[1])(b7_ptr), *(double(*)[1])(b8_ptr), *(double(*)[1])(b9_ptr));
  }
  measure_stop_();
}
