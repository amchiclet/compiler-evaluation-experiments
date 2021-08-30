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


double (*v00_ptr);
double (*v01_ptr);
double (*v02_ptr);
double (*v03_ptr);
double (*v04_ptr);
double (*v05_ptr);
double (*v06_ptr);
double (*v07_ptr);
double (*v08_ptr);
double (*v09_ptr);
double (*v10_ptr);
double (*v11_ptr);
double (*v12_ptr);
double (*v13_ptr);
double (*v14_ptr);
double (*v15_ptr);
double (*v16_ptr);
double (*v17_ptr);
double (*v18_ptr);
double (*v19_ptr);

void allocate_arrays() {
  v00_ptr = malloc(sizeof(double) * (31999));
  v01_ptr = malloc(sizeof(double) * (31999));
  v02_ptr = malloc(sizeof(double) * (31999));
  v03_ptr = malloc(sizeof(double) * (31999));
  v04_ptr = malloc(sizeof(double) * (31999));
  v05_ptr = malloc(sizeof(double) * (31999));
  v06_ptr = malloc(sizeof(double) * (31999));
  v07_ptr = malloc(sizeof(double) * (31999));
  v08_ptr = malloc(sizeof(double) * (31999));
  v09_ptr = malloc(sizeof(double) * (31999));
  v10_ptr = malloc(sizeof(double) * (31999));
  v11_ptr = malloc(sizeof(double) * (31999));
  v12_ptr = malloc(sizeof(double) * (31999));
  v13_ptr = malloc(sizeof(double) * (31999));
  v14_ptr = malloc(sizeof(double) * (1));
  v15_ptr = malloc(sizeof(double) * (1));
  v16_ptr = malloc(sizeof(double) * (1));
  v17_ptr = malloc(sizeof(double) * (1));
  v18_ptr = malloc(sizeof(double) * (1));
  v19_ptr = malloc(sizeof(double) * (1));
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

}

void init_arrays(double v00[restrict 31999], double v01[restrict 31999], double v02[restrict 31999], double v03[restrict 31999], double v04[restrict 31999], double v05[restrict 31999], double v06[restrict 31999], double v07[restrict 31999], double v08[restrict 31999], double v09[restrict 31999], double v10[restrict 31999], double v11[restrict 31999], double v12[restrict 31999], double v13[restrict 31999], double v14[restrict 1], double v15[restrict 1], double v16[restrict 1], double v17[restrict 1], double v18[restrict 1], double v19[restrict 1]) {
  for (int i0 = 0; i0 <= 31998; ++i0) {
    v00[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 31998; ++i0) {
    v01[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 31998; ++i0) {
    v02[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 31998; ++i0) {
    v03[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 31998; ++i0) {
    v04[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 31998; ++i0) {
    v05[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 31998; ++i0) {
    v06[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 31998; ++i0) {
    v07[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 31998; ++i0) {
    v08[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 31998; ++i0) {
    v09[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 31998; ++i0) {
    v10[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 31998; ++i0) {
    v11[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 31998; ++i0) {
    v12[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 31998; ++i0) {
    v13[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 0; ++i0) {
    v14[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 0; ++i0) {
    v15[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 0; ++i0) {
    v16[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 0; ++i0) {
    v17[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 0; ++i0) {
    v18[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 0; ++i0) {
    v19[i0] = drand(0.0, 1.0);
  }
}

void init_array_ptrs() {
  init_arrays(*(double(*)[31999])(v00_ptr), *(double(*)[31999])(v01_ptr), *(double(*)[31999])(v02_ptr), *(double(*)[31999])(v03_ptr), *(double(*)[31999])(v04_ptr), *(double(*)[31999])(v05_ptr), *(double(*)[31999])(v06_ptr), *(double(*)[31999])(v07_ptr), *(double(*)[31999])(v08_ptr), *(double(*)[31999])(v09_ptr), *(double(*)[31999])(v10_ptr), *(double(*)[31999])(v11_ptr), *(double(*)[31999])(v12_ptr), *(double(*)[31999])(v13_ptr), *(double(*)[1])(v14_ptr), *(double(*)[1])(v15_ptr), *(double(*)[1])(v16_ptr), *(double(*)[1])(v17_ptr), *(double(*)[1])(v18_ptr), *(double(*)[1])(v19_ptr));
}

void measure_init_();
void measure_start_();
void measure_stop_();

int core(double v00[restrict 31999], double v01[restrict 31999], double v02[restrict 31999], double v03[restrict 31999], double v04[restrict 31999], double v05[restrict 31999], double v06[restrict 31999], double v07[restrict 31999], double v08[restrict 31999], double v09[restrict 31999], double v10[restrict 31999], double v11[restrict 31999], double v12[restrict 31999], double v13[restrict 31999], double v14[restrict 1], double v15[restrict 1], double v16[restrict 1], double v17[restrict 1], double v18[restrict 1], double v19[restrict 1]);

void measure(int n_iterations, int n_elements) {
  srand(0);
  init_scalars(n_elements);
  allocate_arrays();
  init_array_ptrs();

  measure_init_();
  measure_start_();
  for (int i = 0; i < n_iterations; ++i) {
    core(*(double(*)[31999])(v00_ptr), *(double(*)[31999])(v01_ptr), *(double(*)[31999])(v02_ptr), *(double(*)[31999])(v03_ptr), *(double(*)[31999])(v04_ptr), *(double(*)[31999])(v05_ptr), *(double(*)[31999])(v06_ptr), *(double(*)[31999])(v07_ptr), *(double(*)[31999])(v08_ptr), *(double(*)[31999])(v09_ptr), *(double(*)[31999])(v10_ptr), *(double(*)[31999])(v11_ptr), *(double(*)[31999])(v12_ptr), *(double(*)[31999])(v13_ptr), *(double(*)[1])(v14_ptr), *(double(*)[1])(v15_ptr), *(double(*)[1])(v16_ptr), *(double(*)[1])(v17_ptr), *(double(*)[1])(v18_ptr), *(double(*)[1])(v19_ptr));
  }
  measure_stop_();
}
