#include <x86intrin.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <assert.h>
#include <limits.h>
#include <string.h>

int read_arguments (int *n_iterations) {
  FILE *file = fopen ("codelet.data", "r");
  if (file == NULL) {
    return 0;
  }

  int dont_care;
  int n_read = fscanf(file, "%d %d", n_iterations, &dont_care);
  fclose(file);
  return n_read == 2;
}

void measure(int n_iterations);

int main(int argc, char **argv) {
  // read arguments
  int n_iterations;
  if (!read_arguments(&n_iterations)) {
    printf("Failed to load codelet.data\n");
    return 1;
  }

  // measure
  printf("Measuring with %d iterations\n", n_iterations);
  measure(n_iterations);

  return 0;
}

