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

int inner_loops;
double (*Dex1_ptr);
double (*Dex12_ptr);
double (*Ex1_ptr);
double (*Ex12_ptr);
int (*Ir_ptr);
int (*Ir2_ptr);
double (*Rx_ptr);
double (*Rx2_ptr);
double (*Vx_ptr);
double (*Vx2_ptr);
double (*Xi_ptr);
double (*Xi2_ptr);
double (*Xtra_ptr);
double (*Xtra2_ptr);
double (*Xx_ptr);
double (*Xx2_ptr);

void allocate_arrays() {
  Dex1_ptr = malloc(sizeof(double) * (1001));
  Dex12_ptr = malloc(sizeof(double) * (1001));
  Ex1_ptr = malloc(sizeof(double) * (1001));
  Ex12_ptr = malloc(sizeof(double) * (1001));
  Ir_ptr = malloc(sizeof(int) * (1001));
  Ir2_ptr = malloc(sizeof(int) * (1001));
  Rx_ptr = malloc(sizeof(double) * (1001));
  Rx2_ptr = malloc(sizeof(double) * (1001));
  Vx_ptr = malloc(sizeof(double) * (1001));
  Vx2_ptr = malloc(sizeof(double) * (1001));
  Xi_ptr = malloc(sizeof(double) * (1001));
  Xi2_ptr = malloc(sizeof(double) * (1001));
  Xtra_ptr = malloc(sizeof(double) * (40));
  Xtra2_ptr = malloc(sizeof(double) * (1));
  Xx_ptr = malloc(sizeof(double) * (1001));
  Xx2_ptr = malloc(sizeof(double) * (1001));
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
  inner_loops = 1000;
}

void init_arrays(double Dex1[restrict 1001], double Dex12[restrict 1001], double Ex1[restrict 1001], double Ex12[restrict 1001], int Ir[restrict 1001], int Ir2[restrict 1001], double Rx[restrict 1001], double Rx2[restrict 1001], double Vx[restrict 1001], double Vx2[restrict 1001], double Xi[restrict 1001], double Xi2[restrict 1001], double Xtra[restrict 40], double Xtra2[restrict 1], double Xx[restrict 1001], double Xx2[restrict 1001]) {
  for (int i0 = 0; i0 <= 1000; ++i0) {
    Dex1[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 1000; ++i0) {
    Dex12[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 1000; ++i0) {
    Ex1[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 1000; ++i0) {
    Ex12[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 1000; ++i0) {
    Ir[i0] = irand(0, 10);
  }
  for (int i0 = 0; i0 <= 1000; ++i0) {
    Ir2[i0] = irand(0, 10);
  }
  for (int i0 = 0; i0 <= 1000; ++i0) {
    Rx[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 1000; ++i0) {
    Rx2[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 1000; ++i0) {
    Vx[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 1000; ++i0) {
    Vx2[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 1000; ++i0) {
    Xi[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 1000; ++i0) {
    Xi2[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 27; i0 <= 27; ++i0) {
    Xtra[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 0; ++i0) {
    Xtra2[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 1000; ++i0) {
    Xx[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 1000; ++i0) {
    Xx2[i0] = drand(0.0, 1.0);
  }
}

void init_array_ptrs() {
  init_arrays(*(double(*)[1001])(Dex1_ptr), *(double(*)[1001])(Dex12_ptr), *(double(*)[1001])(Ex1_ptr), *(double(*)[1001])(Ex12_ptr), *(int(*)[1001])(Ir_ptr), *(int(*)[1001])(Ir2_ptr), *(double(*)[1001])(Rx_ptr), *(double(*)[1001])(Rx2_ptr), *(double(*)[1001])(Vx_ptr), *(double(*)[1001])(Vx2_ptr), *(double(*)[1001])(Xi_ptr), *(double(*)[1001])(Xi2_ptr), *(double(*)[40])(Xtra_ptr), *(double(*)[1])(Xtra2_ptr), *(double(*)[1001])(Xx_ptr), *(double(*)[1001])(Xx2_ptr));
}

void measure_init_();
void measure_start_();
void measure_stop_();

int core(double Dex1[restrict 1001], double Dex12[restrict 1001], double Ex1[restrict 1001], double Ex12[restrict 1001], int Ir[restrict 1001], int Ir2[restrict 1001], double Rx[restrict 1001], double Rx2[restrict 1001], double Vx[restrict 1001], double Vx2[restrict 1001], double Xi[restrict 1001], double Xi2[restrict 1001], double Xtra[restrict 40], double Xtra2[restrict 1], double Xx[restrict 1001], double Xx2[restrict 1001]);

void measure(int n_iterations, int n_elements) {
  srand(0);
  init_scalars(n_elements);
  allocate_arrays();
  init_array_ptrs();

  measure_init_();
  measure_start_();
  for (int i = 0; i < n_iterations; ++i) {
    core(*(double(*)[1001])(Dex1_ptr), *(double(*)[1001])(Dex12_ptr), *(double(*)[1001])(Ex1_ptr), *(double(*)[1001])(Ex12_ptr), *(int(*)[1001])(Ir_ptr), *(int(*)[1001])(Ir2_ptr), *(double(*)[1001])(Rx_ptr), *(double(*)[1001])(Rx2_ptr), *(double(*)[1001])(Vx_ptr), *(double(*)[1001])(Vx2_ptr), *(double(*)[1001])(Xi_ptr), *(double(*)[1001])(Xi2_ptr), *(double(*)[40])(Xtra_ptr), *(double(*)[1])(Xtra2_ptr), *(double(*)[1001])(Xx_ptr), *(double(*)[1001])(Xx2_ptr));
  }
  measure_stop_();
}
