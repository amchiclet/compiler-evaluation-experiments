#include <x86intrin.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <assert.h>
#include <limits.h>
#include <string.h>

unsigned long long core(float A[restrict 35], float B[restrict 61], float C[restrict 43], float D[restrict 53], float E[restrict 58]);

struct Data {
  float (*A)[35];
  float (*B)[61];
  float (*C)[43];
  float (*D)[53];
  float (*E)[58];
};

float frand(float min, float max) {
  float scale = rand() / (float) RAND_MAX;
  return min + scale * (max - min);
}

float irand(int min, int max) {
  return min + (rand() % (max - min));
}

void *allocate() {
  struct Data *data = malloc(sizeof(struct Data));
  data->A = malloc(sizeof(float) * 35);
  data->B = malloc(sizeof(float) * 61);
  data->C = malloc(sizeof(float) * 43);
  data->D = malloc(sizeof(float) * 53);
  data->E = malloc(sizeof(float) * 58);
  return (void*)data;
}

void init_inner(float A[restrict 35], float B[restrict 61], float C[restrict 43], float D[restrict 53], float E[restrict 58]) {
  allocate();
  for (int i0 = 0; i0 <= 34; ++i0) {
    float v = frand(0.0, 1.0);
    A[i0] = v;
  }
  for (int i0 = 0; i0 <= 60; ++i0) {
    float v = frand(0.0, 1.0);
    B[i0] = v;
  }
  for (int i0 = 0; i0 <= 42; ++i0) {
    float v = frand(0.0, 1.0);
    C[i0] = v;
  }
  for (int i0 = 0; i0 <= 52; ++i0) {
    float v = frand(0.0, 1.0);
    D[i0] = v;
  }
  for (int i0 = 0; i0 <= 57; ++i0) {
    float v = frand(0.0, 1.0);
    E[i0] = v;
  }
}

float checksum_inner(float A[restrict 35], float B[restrict 61], float C[restrict 43], float D[restrict 53], float E[restrict 58]) {
  float total = 0.0;
  for (int i0 = 0; i0 <= 34; ++i0) {
    total += A[i0];
  }
  for (int i0 = 0; i0 <= 60; ++i0) {
    total += B[i0];
  }
  for (int i0 = 0; i0 <= 42; ++i0) {
    total += C[i0];
  }
  for (int i0 = 0; i0 <= 52; ++i0) {
    total += D[i0];
  }
  for (int i0 = 0; i0 <= 57; ++i0) {
    total += E[i0];
  }
  return total;
}

void init(void *void_ptr) {
  struct Data *data = (struct Data*)void_ptr;
  return init_inner(*data->A, *data->B, *data->C, *data->D, *data->E);
};

float checksum(void *void_ptr) {
  struct Data *data = (struct Data*)void_ptr;
  return checksum_inner(*data->A, *data->B, *data->C, *data->D, *data->E);
};

unsigned long long kernel(void *void_ptr) {
  struct Data *data = (struct Data*)void_ptr;
  return core(*data->A, *data->B, *data->C, *data->D, *data->E);
};

