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

unsigned long long core(double A[restrict 420][420], double B[restrict 420][420], double C[restrict 1][1], double D[restrict 420][420], double E[restrict 420][420]);

struct Data {
  double (*A)[420][420];
  double (*B)[420][420];
  double (*C)[1][1];
  double (*D)[420][420];
  double (*E)[420][420];
};

float frand(float min, float max) {
  float scale = rand() / (float) RAND_MAX;
  return min + scale * (max - min);
}

float irand(int min, int max) {
  return min + (rand() % (max - min));
}

double drand(double min, double max) {
  double scale = rand() / (double) RAND_MAX;
  return min + scale * (max - min);
}

void *allocate() {
  struct Data *data = malloc(sizeof(struct Data));
  data->A = malloc(sizeof(double) * 420 * 420);
  data->B = malloc(sizeof(double) * 420 * 420);
  data->C = malloc(sizeof(double) * 1 * 1);
  data->D = malloc(sizeof(double) * 420 * 420);
  data->E = malloc(sizeof(double) * 420 * 420);
  return (void*)data;
}

int init_inner(double A[restrict 420][420], double B[restrict 420][420], double C[restrict 1][1], double D[restrict 420][420], double E[restrict 420][420]) {
  for (int i0 = 0; i0 <= 419; ++i0) {
    for (int i1 = 0; i1 <= 419; ++i1) {
      double v = drand(0.0, 1.0);
      A[i0][i1] = v;
    }
  }
  for (int i0 = 0; i0 <= 419; ++i0) {
    for (int i1 = 0; i1 <= 419; ++i1) {
      double v = drand(0.0, 1.0);
      B[i0][i1] = v;
    }
  }
  for (int i0 = 0; i0 <= 0; ++i0) {
    for (int i1 = 0; i1 <= 0; ++i1) {
      double v = drand(0.0, 1.0);
      C[i0][i1] = v;
    }
  }
  for (int i0 = 0; i0 <= 419; ++i0) {
    for (int i1 = 0; i1 <= 419; ++i1) {
      double v = drand(0.0, 1.0);
      D[i0][i1] = v;
    }
  }
  for (int i0 = 0; i0 <= 419; ++i0) {
    for (int i1 = 0; i1 <= 419; ++i1) {
      double v = drand(0.0, 1.0);
      E[i0][i1] = v;
    }
  }
  return 0;
}

int init(void *void_ptr) {
  struct Data *data = (struct Data*)void_ptr;
  return init_inner(*data->A, *data->B, *data->C, *data->D, *data->E);
};

int kernel(void *void_ptr) {
  struct Data *data = (struct Data*)void_ptr;
  return core(*data->A, *data->B, *data->C, *data->D, *data->E);
};

