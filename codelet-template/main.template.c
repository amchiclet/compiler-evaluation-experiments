#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <assert.h>
#include <limits.h>
#include <string.h>

int read_arguments (int *n_iterations, int *n_elements) {
  FILE *file = fopen ("codelet.data", "r");
  if (file == NULL) {
    return 0;
  }

  int n_read = fscanf(file, "%d %d", n_iterations, n_elements);
  fclose(file);
  return n_read == 2;
}

void measure(int n_iterations, int n_elements);

int main(int argc, char **argv) {
  // read arguments
  int n_iterations;
  int n_elements;
  if (!read_arguments(&n_iterations, &n_elements)) {
    printf("Failed to load codelet.data\n");
    return 1;
  }

  // measure
  printf("n_iterations = %d, n_elements = %d\n", n_iterations, n_elements);
  measure(n_iterations, n_elements);

  return 0;
}

