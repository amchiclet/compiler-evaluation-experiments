#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <string.h>

${define_scalars}
${define_arrays_as_pointers}

void allocate_arrays() {
${allocate_arrays_code}
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
${init_scalars_code}
}

void init_arrays(${array_params}) {
${init_arrays_code}
}

void init_array_ptrs() {
  init_arrays(${array_args});
}

void measure_init_();
void measure_start_();
void measure_stop_();

int core(${array_params});

void measure(int n_iterations, int n_elements) {
  srand(0);
  init_scalars(n_elements);
  allocate_arrays();
  init_array_ptrs();

  measure_init_();
  measure_start_();
  for (int i = 0; i < n_iterations; ++i) {
    core(${array_args});
  }
  measure_stop_();
}
