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

int nj;
int nl;
int nm;
double (*C_ptr);
double (*C2_ptr);
double (*C3_ptr);
double (*C4_ptr);
double (*C5_ptr);
double (*C6_ptr);
double (*C7_ptr);
double (*C8_ptr);
double (*D_ptr);
double (*D2_ptr);
double (*D3_ptr);
double (*D4_ptr);
double (*D5_ptr);
double (*D6_ptr);
double (*D7_ptr);
double (*D8_ptr);
double (*F_ptr);
double (*F2_ptr);
double (*F3_ptr);
double (*F4_ptr);
double (*F5_ptr);
double (*F6_ptr);
double (*F7_ptr);
double (*F8_ptr);

void allocate_arrays() {
  C_ptr = malloc(sizeof(double) * (900) * (1200));
  C2_ptr = malloc(sizeof(double) * (900) * (1200));
  C3_ptr = malloc(sizeof(double) * (1) * (1));
  C4_ptr = malloc(sizeof(double) * (1) * (1));
  C5_ptr = malloc(sizeof(double) * (1) * (1));
  C6_ptr = malloc(sizeof(double) * (1) * (1));
  C7_ptr = malloc(sizeof(double) * (1) * (1));
  C8_ptr = malloc(sizeof(double) * (1) * (1));
  D_ptr = malloc(sizeof(double) * (1200) * (1100));
  D2_ptr = malloc(sizeof(double) * (1200) * (1100));
  D3_ptr = malloc(sizeof(double) * (1) * (1));
  D4_ptr = malloc(sizeof(double) * (1) * (1));
  D5_ptr = malloc(sizeof(double) * (1) * (1));
  D6_ptr = malloc(sizeof(double) * (1) * (1));
  D7_ptr = malloc(sizeof(double) * (1) * (1));
  D8_ptr = malloc(sizeof(double) * (1) * (1));
  F_ptr = malloc(sizeof(double) * (900) * (1100));
  F2_ptr = malloc(sizeof(double) * (900) * (1100));
  F3_ptr = malloc(sizeof(double) * (900) * (1100));
  F4_ptr = malloc(sizeof(double) * (900) * (1100));
  F5_ptr = malloc(sizeof(double) * (900) * (1100));
  F6_ptr = malloc(sizeof(double) * (900) * (1100));
  F7_ptr = malloc(sizeof(double) * (900) * (1100));
  F8_ptr = malloc(sizeof(double) * (900) * (1100));
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
  nj = 900;
  nl = 1100;
  nm = 1200;
}

void init_arrays(double C[restrict 900][1200], double C2[restrict 900][1200], double C3[restrict 1][1], double C4[restrict 1][1], double C5[restrict 1][1], double C6[restrict 1][1], double C7[restrict 1][1], double C8[restrict 1][1], double D[restrict 1200][1100], double D2[restrict 1200][1100], double D3[restrict 1][1], double D4[restrict 1][1], double D5[restrict 1][1], double D6[restrict 1][1], double D7[restrict 1][1], double D8[restrict 1][1], double F[restrict 900][1100], double F2[restrict 900][1100], double F3[restrict 900][1100], double F4[restrict 900][1100], double F5[restrict 900][1100], double F6[restrict 900][1100], double F7[restrict 900][1100], double F8[restrict 900][1100]) {
  for (int i0 = 0; i0 <= 899; ++i0) {
    for (int i1 = 0; i1 <= 1199; ++i1) {
      C[i0][i1] = drand(0.0, 1.0);
    }
  }
  for (int i0 = 0; i0 <= 899; ++i0) {
    for (int i1 = 0; i1 <= 1199; ++i1) {
      C2[i0][i1] = drand(0.0, 1.0);
    }
  }
  for (int i0 = 0; i0 <= 0; ++i0) {
    for (int i1 = 0; i1 <= 0; ++i1) {
      C3[i0][i1] = drand(0.0, 1.0);
    }
  }
  for (int i0 = 0; i0 <= 0; ++i0) {
    for (int i1 = 0; i1 <= 0; ++i1) {
      C4[i0][i1] = drand(0.0, 1.0);
    }
  }
  for (int i0 = 0; i0 <= 0; ++i0) {
    for (int i1 = 0; i1 <= 0; ++i1) {
      C5[i0][i1] = drand(0.0, 1.0);
    }
  }
  for (int i0 = 0; i0 <= 0; ++i0) {
    for (int i1 = 0; i1 <= 0; ++i1) {
      C6[i0][i1] = drand(0.0, 1.0);
    }
  }
  for (int i0 = 0; i0 <= 0; ++i0) {
    for (int i1 = 0; i1 <= 0; ++i1) {
      C7[i0][i1] = drand(0.0, 1.0);
    }
  }
  for (int i0 = 0; i0 <= 0; ++i0) {
    for (int i1 = 0; i1 <= 0; ++i1) {
      C8[i0][i1] = drand(0.0, 1.0);
    }
  }
  for (int i0 = 0; i0 <= 1199; ++i0) {
    for (int i1 = 0; i1 <= 1099; ++i1) {
      D[i0][i1] = drand(0.0, 1.0);
    }
  }
  for (int i0 = 0; i0 <= 1199; ++i0) {
    for (int i1 = 0; i1 <= 1099; ++i1) {
      D2[i0][i1] = drand(0.0, 1.0);
    }
  }
  for (int i0 = 0; i0 <= 0; ++i0) {
    for (int i1 = 0; i1 <= 0; ++i1) {
      D3[i0][i1] = drand(0.0, 1.0);
    }
  }
  for (int i0 = 0; i0 <= 0; ++i0) {
    for (int i1 = 0; i1 <= 0; ++i1) {
      D4[i0][i1] = drand(0.0, 1.0);
    }
  }
  for (int i0 = 0; i0 <= 0; ++i0) {
    for (int i1 = 0; i1 <= 0; ++i1) {
      D5[i0][i1] = drand(0.0, 1.0);
    }
  }
  for (int i0 = 0; i0 <= 0; ++i0) {
    for (int i1 = 0; i1 <= 0; ++i1) {
      D6[i0][i1] = drand(0.0, 1.0);
    }
  }
  for (int i0 = 0; i0 <= 0; ++i0) {
    for (int i1 = 0; i1 <= 0; ++i1) {
      D7[i0][i1] = drand(0.0, 1.0);
    }
  }
  for (int i0 = 0; i0 <= 0; ++i0) {
    for (int i1 = 0; i1 <= 0; ++i1) {
      D8[i0][i1] = drand(0.0, 1.0);
    }
  }
  for (int i0 = 0; i0 <= 899; ++i0) {
    for (int i1 = 0; i1 <= 1099; ++i1) {
      F[i0][i1] = drand(0.0, 1.0);
    }
  }
  for (int i0 = 0; i0 <= 899; ++i0) {
    for (int i1 = 0; i1 <= 1099; ++i1) {
      F2[i0][i1] = drand(0.0, 1.0);
    }
  }
  for (int i0 = 0; i0 <= 899; ++i0) {
    for (int i1 = 0; i1 <= 1099; ++i1) {
      F3[i0][i1] = drand(0.0, 1.0);
    }
  }
  for (int i0 = 0; i0 <= 899; ++i0) {
    for (int i1 = 0; i1 <= 1099; ++i1) {
      F4[i0][i1] = drand(0.0, 1.0);
    }
  }
  for (int i0 = 0; i0 <= 899; ++i0) {
    for (int i1 = 0; i1 <= 1099; ++i1) {
      F5[i0][i1] = drand(0.0, 1.0);
    }
  }
  for (int i0 = 0; i0 <= 899; ++i0) {
    for (int i1 = 0; i1 <= 1099; ++i1) {
      F6[i0][i1] = drand(0.0, 1.0);
    }
  }
  for (int i0 = 0; i0 <= 899; ++i0) {
    for (int i1 = 0; i1 <= 1099; ++i1) {
      F7[i0][i1] = drand(0.0, 1.0);
    }
  }
  for (int i0 = 0; i0 <= 899; ++i0) {
    for (int i1 = 0; i1 <= 1099; ++i1) {
      F8[i0][i1] = drand(0.0, 1.0);
    }
  }
}

void init_array_ptrs() {
  init_arrays(*(double(*)[900][1200])(C_ptr), *(double(*)[900][1200])(C2_ptr), *(double(*)[1][1])(C3_ptr), *(double(*)[1][1])(C4_ptr), *(double(*)[1][1])(C5_ptr), *(double(*)[1][1])(C6_ptr), *(double(*)[1][1])(C7_ptr), *(double(*)[1][1])(C8_ptr), *(double(*)[1200][1100])(D_ptr), *(double(*)[1200][1100])(D2_ptr), *(double(*)[1][1])(D3_ptr), *(double(*)[1][1])(D4_ptr), *(double(*)[1][1])(D5_ptr), *(double(*)[1][1])(D6_ptr), *(double(*)[1][1])(D7_ptr), *(double(*)[1][1])(D8_ptr), *(double(*)[900][1100])(F_ptr), *(double(*)[900][1100])(F2_ptr), *(double(*)[900][1100])(F3_ptr), *(double(*)[900][1100])(F4_ptr), *(double(*)[900][1100])(F5_ptr), *(double(*)[900][1100])(F6_ptr), *(double(*)[900][1100])(F7_ptr), *(double(*)[900][1100])(F8_ptr));
}

void measure_init_();
void measure_start_();
void measure_stop_();

int core(double C[restrict 900][1200], double C2[restrict 900][1200], double C3[restrict 1][1], double C4[restrict 1][1], double C5[restrict 1][1], double C6[restrict 1][1], double C7[restrict 1][1], double C8[restrict 1][1], double D[restrict 1200][1100], double D2[restrict 1200][1100], double D3[restrict 1][1], double D4[restrict 1][1], double D5[restrict 1][1], double D6[restrict 1][1], double D7[restrict 1][1], double D8[restrict 1][1], double F[restrict 900][1100], double F2[restrict 900][1100], double F3[restrict 900][1100], double F4[restrict 900][1100], double F5[restrict 900][1100], double F6[restrict 900][1100], double F7[restrict 900][1100], double F8[restrict 900][1100]);

void measure(int n_iterations, int n_elements) {
  srand(0);
  init_scalars(n_elements);
  allocate_arrays();
  init_array_ptrs();

  measure_init_();
  measure_start_();
  for (int i = 0; i < n_iterations; ++i) {
    core(*(double(*)[900][1200])(C_ptr), *(double(*)[900][1200])(C2_ptr), *(double(*)[1][1])(C3_ptr), *(double(*)[1][1])(C4_ptr), *(double(*)[1][1])(C5_ptr), *(double(*)[1][1])(C6_ptr), *(double(*)[1][1])(C7_ptr), *(double(*)[1][1])(C8_ptr), *(double(*)[1200][1100])(D_ptr), *(double(*)[1200][1100])(D2_ptr), *(double(*)[1][1])(D3_ptr), *(double(*)[1][1])(D4_ptr), *(double(*)[1][1])(D5_ptr), *(double(*)[1][1])(D6_ptr), *(double(*)[1][1])(D7_ptr), *(double(*)[1][1])(D8_ptr), *(double(*)[900][1100])(F_ptr), *(double(*)[900][1100])(F2_ptr), *(double(*)[900][1100])(F3_ptr), *(double(*)[900][1100])(F4_ptr), *(double(*)[900][1100])(F5_ptr), *(double(*)[900][1100])(F6_ptr), *(double(*)[900][1100])(F7_ptr), *(double(*)[900][1100])(F8_ptr));
  }
  measure_stop_();
}
