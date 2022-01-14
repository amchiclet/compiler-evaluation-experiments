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
int scalar4;
int scalar5;
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
double (*Arr15_ptr);
double (*Arr16_ptr);
double (*Arr17_ptr);
double (*Arr18_ptr);
double (*Arr19_ptr);
double (*Arr20_ptr);
double (*Arr21_ptr);
double (*Arr22_ptr);
double (*Arr23_ptr);
double (*Arr24_ptr);
double (*Arr25_ptr);

void allocate_arrays() {
  Arr01_ptr = malloc(sizeof(double) * (32000));
  Arr02_ptr = malloc(sizeof(double) * (32000));
  Arr03_ptr = malloc(sizeof(double) * (32000));
  Arr04_ptr = malloc(sizeof(double) * (32000));
  Arr05_ptr = malloc(sizeof(double) * (32000));
  Arr06_ptr = malloc(sizeof(double) * (32000));
  Arr07_ptr = malloc(sizeof(double) * (32000));
  Arr08_ptr = malloc(sizeof(double) * (1));
  Arr09_ptr = malloc(sizeof(double) * (32000));
  Arr10_ptr = malloc(sizeof(double) * (32000));
  Arr11_ptr = malloc(sizeof(double) * (1));
  Arr12_ptr = malloc(sizeof(double) * (1));
  Arr13_ptr = malloc(sizeof(double) * (1));
  Arr14_ptr = malloc(sizeof(double) * (1));
  Arr15_ptr = malloc(sizeof(double) * (1));
  Arr16_ptr = malloc(sizeof(double) * (1));
  Arr17_ptr = malloc(sizeof(double) * (1));
  Arr18_ptr = malloc(sizeof(double) * (1));
  Arr19_ptr = malloc(sizeof(double) * (1));
  Arr20_ptr = malloc(sizeof(double) * (1));
  Arr21_ptr = malloc(sizeof(double) * (1));
  Arr22_ptr = malloc(sizeof(double) * (1));
  Arr23_ptr = malloc(sizeof(double) * (1));
  Arr24_ptr = malloc(sizeof(double) * (1));
  Arr25_ptr = malloc(sizeof(double) * (1));
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
  scalar4 = irand(0, 10);
  scalar5 = irand(0, 10);
  size = 32000;
}

void init_arrays(double Arr01[restrict 32000], double Arr02[restrict 32000], double Arr03[restrict 32000], double Arr04[restrict 32000], double Arr05[restrict 32000], double Arr06[restrict 32000], double Arr07[restrict 32000], double Arr08[restrict 1], double Arr09[restrict 32000], double Arr10[restrict 32000], double Arr11[restrict 1], double Arr12[restrict 1], double Arr13[restrict 1], double Arr14[restrict 1], double Arr15[restrict 1], double Arr16[restrict 1], double Arr17[restrict 1], double Arr18[restrict 1], double Arr19[restrict 1], double Arr20[restrict 1], double Arr21[restrict 1], double Arr22[restrict 1], double Arr23[restrict 1], double Arr24[restrict 1], double Arr25[restrict 1]) {
  for (int i0 = 0; i0 <= 31999; ++i0) {
    Arr01[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 31999; ++i0) {
    Arr02[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 31999; ++i0) {
    Arr03[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 31999; ++i0) {
    Arr04[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 31999; ++i0) {
    Arr05[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 31999; ++i0) {
    Arr06[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 31999; ++i0) {
    Arr07[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 0; ++i0) {
    Arr08[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 31999; ++i0) {
    Arr09[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 31999; ++i0) {
    Arr10[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 0; ++i0) {
    Arr11[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 0; ++i0) {
    Arr12[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 0; ++i0) {
    Arr13[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 0; ++i0) {
    Arr14[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 0; ++i0) {
    Arr15[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 0; ++i0) {
    Arr16[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 0; ++i0) {
    Arr17[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 0; ++i0) {
    Arr18[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 0; ++i0) {
    Arr19[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 0; ++i0) {
    Arr20[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 0; ++i0) {
    Arr21[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 0; ++i0) {
    Arr22[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 0; ++i0) {
    Arr23[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 0; ++i0) {
    Arr24[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 0; ++i0) {
    Arr25[i0] = drand(0.0, 1.0);
  }
}

void init_array_ptrs() {
  init_arrays(*(double(*)[32000])(Arr01_ptr), *(double(*)[32000])(Arr02_ptr), *(double(*)[32000])(Arr03_ptr), *(double(*)[32000])(Arr04_ptr), *(double(*)[32000])(Arr05_ptr), *(double(*)[32000])(Arr06_ptr), *(double(*)[32000])(Arr07_ptr), *(double(*)[1])(Arr08_ptr), *(double(*)[32000])(Arr09_ptr), *(double(*)[32000])(Arr10_ptr), *(double(*)[1])(Arr11_ptr), *(double(*)[1])(Arr12_ptr), *(double(*)[1])(Arr13_ptr), *(double(*)[1])(Arr14_ptr), *(double(*)[1])(Arr15_ptr), *(double(*)[1])(Arr16_ptr), *(double(*)[1])(Arr17_ptr), *(double(*)[1])(Arr18_ptr), *(double(*)[1])(Arr19_ptr), *(double(*)[1])(Arr20_ptr), *(double(*)[1])(Arr21_ptr), *(double(*)[1])(Arr22_ptr), *(double(*)[1])(Arr23_ptr), *(double(*)[1])(Arr24_ptr), *(double(*)[1])(Arr25_ptr));
}

void measure_init_();
void measure_start_();
void measure_stop_();

int core(double Arr01[restrict 32000], double Arr02[restrict 32000], double Arr03[restrict 32000], double Arr04[restrict 32000], double Arr05[restrict 32000], double Arr06[restrict 32000], double Arr07[restrict 32000], double Arr08[restrict 1], double Arr09[restrict 32000], double Arr10[restrict 32000], double Arr11[restrict 1], double Arr12[restrict 1], double Arr13[restrict 1], double Arr14[restrict 1], double Arr15[restrict 1], double Arr16[restrict 1], double Arr17[restrict 1], double Arr18[restrict 1], double Arr19[restrict 1], double Arr20[restrict 1], double Arr21[restrict 1], double Arr22[restrict 1], double Arr23[restrict 1], double Arr24[restrict 1], double Arr25[restrict 1]);

void measure(int n_iterations, int inputs[16]) {
  srand(0);
  init_scalars(inputs);
  allocate_arrays();
  init_array_ptrs();

  measure_init_();
  measure_start_();
  for (int i = 0; i < n_iterations; ++i) {
    core(*(double(*)[32000])(Arr01_ptr), *(double(*)[32000])(Arr02_ptr), *(double(*)[32000])(Arr03_ptr), *(double(*)[32000])(Arr04_ptr), *(double(*)[32000])(Arr05_ptr), *(double(*)[32000])(Arr06_ptr), *(double(*)[32000])(Arr07_ptr), *(double(*)[1])(Arr08_ptr), *(double(*)[32000])(Arr09_ptr), *(double(*)[32000])(Arr10_ptr), *(double(*)[1])(Arr11_ptr), *(double(*)[1])(Arr12_ptr), *(double(*)[1])(Arr13_ptr), *(double(*)[1])(Arr14_ptr), *(double(*)[1])(Arr15_ptr), *(double(*)[1])(Arr16_ptr), *(double(*)[1])(Arr17_ptr), *(double(*)[1])(Arr18_ptr), *(double(*)[1])(Arr19_ptr), *(double(*)[1])(Arr20_ptr), *(double(*)[1])(Arr21_ptr), *(double(*)[1])(Arr22_ptr), *(double(*)[1])(Arr23_ptr), *(double(*)[1])(Arr24_ptr), *(double(*)[1])(Arr25_ptr));
  }
  measure_stop_();
}
