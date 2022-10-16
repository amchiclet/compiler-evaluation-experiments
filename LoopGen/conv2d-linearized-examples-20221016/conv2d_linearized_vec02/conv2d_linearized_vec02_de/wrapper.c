#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <string.h>

int IFH;
int IFHP;
int IFM;
int IFW;
int IFWP;
int IMG;
int KH;
int KW;
int OFH;
int OFM;
int OFW;
int PH;
int PW;
int SH;
int SW;
double (*filter_ptr);
double (*input_ptr);
double (*output_ptr);

void allocate_arrays() {
  filter_ptr = malloc(sizeof(double) * (((((((OFM / 2) * IFM) / 2) * KH) * KW) * 2) * 2));
  input_ptr = malloc(sizeof(double) * (((((IMG * IFM) / 2) * IFHP) * IFWP) * 2));
  output_ptr = malloc(sizeof(double) * (((((IMG * OFM) / 2) * OFH) * OFW) * 2));
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
  IFH = 7;
  IFHP = 11;
  IFM = 48;
  IFW = 7;
  IFWP = 11;
  IMG = 8;
  KH = 5;
  KW = 5;
  OFH = 7;
  OFM = 128;
  OFW = 7;
  PH = 2;
  PW = 2;
  SH = 1;
  SW = 1;
}

void init_arrays(double (*restrict filter)[((((((OFM / 2) * IFM) / 2) * KH) * KW) * 2) * 2], double (*restrict input)[((((IMG * IFM) / 2) * IFHP) * IFWP) * 2], double (*restrict output)[((((IMG * OFM) / 2) * OFH) * OFW) * 2]) {
  for (int i0 = 0; i0 <= ((((((OFM / 2) * IFM) / 2) * KH) * KW) * 2) * 2 - 1; i0 += 1) {
    (*filter)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= ((((IMG * IFM) / 2) * IFHP) * IFWP) * 2 - 1; i0 += 1) {
    (*input)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= ((((IMG * OFM) / 2) * OFH) * OFW) * 2 - 1; i0 += 1) {
    (*output)[i0] = drand(0.0, 1.0);
  }
}

void init_array_ptrs() {
  init_arrays((double(*)[((((((OFM / 2) * IFM) / 2) * KH) * KW) * 2) * 2])(filter_ptr), (double(*)[((((IMG * IFM) / 2) * IFHP) * IFWP) * 2])(input_ptr), (double(*)[((((IMG * OFM) / 2) * OFH) * OFW) * 2])(output_ptr));
}

void measure_init_();
void measure_start_();
void measure_stop_();

int core(double (*restrict filter)[((((((OFM / 2) * IFM) / 2) * KH) * KW) * 2) * 2], double (*restrict input)[((((IMG * IFM) / 2) * IFHP) * IFWP) * 2], double (*restrict output)[((((IMG * OFM) / 2) * OFH) * OFW) * 2]);

void measure(int n_iterations, int inputs[16]) {
  srand(0);
  init_scalars(inputs);
  allocate_arrays();
  init_array_ptrs();

  measure_init_();
  measure_start_();
  for (int i = 0; i < n_iterations; ++i) {
    core((double(*)[((((((OFM / 2) * IFM) / 2) * KH) * KW) * 2) * 2])(filter_ptr), (double(*)[((((IMG * IFM) / 2) * IFHP) * IFWP) * 2])(input_ptr), (double(*)[((((IMG * OFM) / 2) * OFH) * OFW) * 2])(output_ptr));
  }
  measure_stop_();
}
