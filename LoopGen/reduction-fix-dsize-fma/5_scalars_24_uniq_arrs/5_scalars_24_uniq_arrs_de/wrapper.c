#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <string.h>

int n_unique_arrs;
double scalar1;
double scalar2;
double scalar3;
double scalar4;
double scalar5;
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

void allocate_arrays() {
  Arr01_ptr = malloc(sizeof(double) * (333334));
  Arr02_ptr = malloc(sizeof(double) * (333334));
  Arr03_ptr = malloc(sizeof(double) * (333334));
  Arr04_ptr = malloc(sizeof(double) * (333334));
  Arr05_ptr = malloc(sizeof(double) * (333334));
  Arr06_ptr = malloc(sizeof(double) * (333334));
  Arr07_ptr = malloc(sizeof(double) * (333334));
  Arr08_ptr = malloc(sizeof(double) * (333334));
  Arr09_ptr = malloc(sizeof(double) * (333334));
  Arr10_ptr = malloc(sizeof(double) * (333334));
  Arr11_ptr = malloc(sizeof(double) * (333334));
  Arr12_ptr = malloc(sizeof(double) * (333334));
  Arr13_ptr = malloc(sizeof(double) * (333334));
  Arr14_ptr = malloc(sizeof(double) * (333334));
  Arr15_ptr = malloc(sizeof(double) * (333334));
  Arr16_ptr = malloc(sizeof(double) * (333334));
  Arr17_ptr = malloc(sizeof(double) * (333334));
  Arr18_ptr = malloc(sizeof(double) * (333334));
  Arr19_ptr = malloc(sizeof(double) * (333334));
  Arr20_ptr = malloc(sizeof(double) * (333334));
  Arr21_ptr = malloc(sizeof(double) * (333334));
  Arr22_ptr = malloc(sizeof(double) * (333334));
  Arr23_ptr = malloc(sizeof(double) * (333334));
  Arr24_ptr = malloc(sizeof(double) * (333334));
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
  n_unique_arrs = inputs[1];
  scalar1 = drand(0.0, 1.0);
  scalar2 = drand(0.0, 1.0);
  scalar3 = drand(0.0, 1.0);
  scalar4 = drand(0.0, 1.0);
  scalar5 = drand(0.0, 1.0);
  size = inputs[0];
}

void init_arrays(double (*restrict Arr01)[333334], double (*restrict Arr02)[333334], double (*restrict Arr03)[333334], double (*restrict Arr04)[333334], double (*restrict Arr05)[333334], double (*restrict Arr06)[333334], double (*restrict Arr07)[333334], double (*restrict Arr08)[333334], double (*restrict Arr09)[333334], double (*restrict Arr10)[333334], double (*restrict Arr11)[333334], double (*restrict Arr12)[333334], double (*restrict Arr13)[333334], double (*restrict Arr14)[333334], double (*restrict Arr15)[333334], double (*restrict Arr16)[333334], double (*restrict Arr17)[333334], double (*restrict Arr18)[333334], double (*restrict Arr19)[333334], double (*restrict Arr20)[333334], double (*restrict Arr21)[333334], double (*restrict Arr22)[333334], double (*restrict Arr23)[333334], double (*restrict Arr24)[333334]) {
  for (int i0 = 0; i0 <= 333333; i0 += 1) {
    (*Arr01)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 333333; i0 += 1) {
    (*Arr02)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 333333; i0 += 1) {
    (*Arr03)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 333333; i0 += 1) {
    (*Arr04)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 333333; i0 += 1) {
    (*Arr05)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 333333; i0 += 1) {
    (*Arr06)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 333333; i0 += 1) {
    (*Arr07)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 333333; i0 += 1) {
    (*Arr08)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 333333; i0 += 1) {
    (*Arr09)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 333333; i0 += 1) {
    (*Arr10)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 333333; i0 += 1) {
    (*Arr11)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 333333; i0 += 1) {
    (*Arr12)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 333333; i0 += 1) {
    (*Arr13)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 333333; i0 += 1) {
    (*Arr14)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 333333; i0 += 1) {
    (*Arr15)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 333333; i0 += 1) {
    (*Arr16)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 333333; i0 += 1) {
    (*Arr17)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 333333; i0 += 1) {
    (*Arr18)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 333333; i0 += 1) {
    (*Arr19)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 333333; i0 += 1) {
    (*Arr20)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 333333; i0 += 1) {
    (*Arr21)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 333333; i0 += 1) {
    (*Arr22)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 333333; i0 += 1) {
    (*Arr23)[i0] = drand(0.0, 1.0);
  }
  for (int i0 = 0; i0 <= 333333; i0 += 1) {
    (*Arr24)[i0] = drand(0.0, 1.0);
  }
}

void init_array_ptrs() {
  init_arrays((double(*)[333334])(Arr01_ptr), (double(*)[333334])(Arr02_ptr), (double(*)[333334])(Arr03_ptr), (double(*)[333334])(Arr04_ptr), (double(*)[333334])(Arr05_ptr), (double(*)[333334])(Arr06_ptr), (double(*)[333334])(Arr07_ptr), (double(*)[333334])(Arr08_ptr), (double(*)[333334])(Arr09_ptr), (double(*)[333334])(Arr10_ptr), (double(*)[333334])(Arr11_ptr), (double(*)[333334])(Arr12_ptr), (double(*)[333334])(Arr13_ptr), (double(*)[333334])(Arr14_ptr), (double(*)[333334])(Arr15_ptr), (double(*)[333334])(Arr16_ptr), (double(*)[333334])(Arr17_ptr), (double(*)[333334])(Arr18_ptr), (double(*)[333334])(Arr19_ptr), (double(*)[333334])(Arr20_ptr), (double(*)[333334])(Arr21_ptr), (double(*)[333334])(Arr22_ptr), (double(*)[333334])(Arr23_ptr), (double(*)[333334])(Arr24_ptr));
}

void measure_init_();
void measure_start_();
void measure_stop_();

int core(double (*restrict Arr01)[333334], double (*restrict Arr02)[333334], double (*restrict Arr03)[333334], double (*restrict Arr04)[333334], double (*restrict Arr05)[333334], double (*restrict Arr06)[333334], double (*restrict Arr07)[333334], double (*restrict Arr08)[333334], double (*restrict Arr09)[333334], double (*restrict Arr10)[333334], double (*restrict Arr11)[333334], double (*restrict Arr12)[333334], double (*restrict Arr13)[333334], double (*restrict Arr14)[333334], double (*restrict Arr15)[333334], double (*restrict Arr16)[333334], double (*restrict Arr17)[333334], double (*restrict Arr18)[333334], double (*restrict Arr19)[333334], double (*restrict Arr20)[333334], double (*restrict Arr21)[333334], double (*restrict Arr22)[333334], double (*restrict Arr23)[333334], double (*restrict Arr24)[333334]);

void measure(int n_iterations, int inputs[16]) {
  srand(0);
  init_scalars(inputs);
  allocate_arrays();
  init_array_ptrs();

  measure_init_();
  measure_start_();
  for (int i = 0; i < n_iterations; ++i) {
    core((double(*)[333334])(Arr01_ptr), (double(*)[333334])(Arr02_ptr), (double(*)[333334])(Arr03_ptr), (double(*)[333334])(Arr04_ptr), (double(*)[333334])(Arr05_ptr), (double(*)[333334])(Arr06_ptr), (double(*)[333334])(Arr07_ptr), (double(*)[333334])(Arr08_ptr), (double(*)[333334])(Arr09_ptr), (double(*)[333334])(Arr10_ptr), (double(*)[333334])(Arr11_ptr), (double(*)[333334])(Arr12_ptr), (double(*)[333334])(Arr13_ptr), (double(*)[333334])(Arr14_ptr), (double(*)[333334])(Arr15_ptr), (double(*)[333334])(Arr16_ptr), (double(*)[333334])(Arr17_ptr), (double(*)[333334])(Arr18_ptr), (double(*)[333334])(Arr19_ptr), (double(*)[333334])(Arr20_ptr), (double(*)[333334])(Arr21_ptr), (double(*)[333334])(Arr22_ptr), (double(*)[333334])(Arr23_ptr), (double(*)[333334])(Arr24_ptr));
  }
  measure_stop_();
}
