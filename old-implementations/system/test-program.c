for [i, j] {
  A[2*i-5][j+2] = A[i-1][j+1] * B[i];
}
Mutation 1
  for [j, i] {
    A[2*i-5][j+2] = A[i-1][j+1] * B[i];
  }
Loop var ranges:
  i = [5..500]
  j = [0..500]
Sorted indices:
  A[0] => ['i-1', '2*i-5']
  B[0] => ['i']
  A[1] => ['j+1', 'j+2']
Array index ranges:
  |A[0]| => [4..995]
  |B[0]| => [5..500]
  |A[1]| => [1..502]
{'A': [996, 503], 'B': [501]}

#include <x86intrin.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <limits.h>
#include <string.h>

float (*A)[996][503];
float (*B)[501];

float frand(float min, float max) {
  float scale = rand() / (float) RAND_MAX;
  return min + scale * (max - min);
}


float irand(int min, int max) {
  return min + (rand() % (max - min));
}

void init() {
  A = malloc(sizeof(float) * 996 * 503);
  for (int i_0 = 0; i_0 < 996; ++i_0) {
    for (int i_1 = 0; i_1 < 503; ++i_1) {
      float v = frand(0.0, 1.0);
      (*A)[i_0][i_1] = v;
    }
  }
  B = malloc(sizeof(float) * 501);
  for (int i_0 = 0; i_0 < 501; ++i_0) {
    float v = frand(0.0, 1.0);
    (*B)[i_0] = v;
  }
}
clock_t kernel() {
  clock_t before = clock();
    for (int i = 5; i < 500 + 1; ++i) {
      for (int j = 0; j < 500 + 1; ++j) {
        (*A)[2 * i - 5][j + 2] = (*A)[i - 1][j + 1] * (*B)[i];
      }
    }
  clock_t after = clock();
  return after - before;
}
int check() {
  int (*A_ref)[996][503];
  int (*A_test)[996][503];
  int (*B_ref)[501];
  int (*B_test)[501];
  // Initialization
  A_ref = malloc(sizeof(int) * 996 * 503);
  A_test = malloc(sizeof(int) * 996 * 503);
  for (int i_0 = 0; i_0 < 996; ++i_0) {
    for (int i_1 = 0; i_1 < 503; ++i_1) {
      int v = irand(1, 10);
      (*A_ref)[i_0][i_1] = v;
      (*A_test)[i_0][i_1] = v;
    }
  }
  B_ref = malloc(sizeof(int) * 501);
  B_test = malloc(sizeof(int) * 501);
  for (int i_0 = 0; i_0 < 501; ++i_0) {
    int v = irand(1, 10);
    (*B_ref)[i_0] = v;
    (*B_test)[i_0] = v;
  }
  // Test program
  for (int i = 5; i < 500 + 1; ++i) {
    for (int j = 0; j < 500 + 1; ++j) {
      (*A_test)[2 * i - 5][j + 2] = (*A_test)[i - 1][j + 1] * (*B_test)[i];
    }
  }
  // Reference program
  for (int j = 0; j < 500 + 1; ++j) {
    for (int i = 5; i < 500 + 1; ++i) {
      (*A_ref)[2 * i - 5][j + 2] = (*A_ref)[i - 1][j + 1] * (*B_ref)[i];
    }
  }
  // Compare the results
  for (int i_0 = 0; i_0 < 996; ++i_0) {
    for (int i_1 = 0; i_1 < 503; ++i_1) {
      if ((*A_test)[i_0][i_1] != (*A_ref)[i_0][i_1]) return 0;
    }
  }
  for (int i_0 = 0; i_0 < 501; ++i_0) {
    if ((*B_test)[i_0] != (*B_ref)[i_0]) return 0;
  }
  return 1;
}
void checksum() {
  float total = 0.0;
  for (int i_0 = 0; i_0 < 996; ++i_0) {
    for (int i_1 = 0; i_1 < 503; ++i_1) {
      total += (*A)[i_0][i_1];
    }
  }
  for (int i_0 = 0; i_0 < 501; ++i_0) {
    total += (*B)[i_0];
  }
  printf("Checksum is %f\n", total);
}

void run(int n_iterations) {
  // assuming micro seconds
  if (CLOCKS_PER_SEC != 1000000) {
    printf("WARNING: CLOCK_PER_SEC=%ld. Expected micro seconds (1000000).", CLOCKS_PER_SEC);
  }

  int *runtimes = (int*)malloc(n_iterations * sizeof(int));

  for (int i = 0; i < n_iterations; ++i) {
    runtimes[i] = (int)kernel();
  }

  for (int i = 0; i < n_iterations; ++i) {
    printf("Iteration %d %d\n", i+1, runtimes[i]);
  }
  free(runtimes);
}


int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Not enough number of arguments\n");
    return 1;
  }

  srand(0);
  if (strcmp(argv[1], "--measure") == 0) {
    if (argc < 3) {
      printf("Not enough number of arguments for measure mode\n");
      return 1;
    }
    int n_iterations = atoi(argv[2]);
    printf("Measuring with %d iterations\n", n_iterations);
    init();
    run(n_iterations);
    return 0;
  } else if (strcmp(argv[1], "--test") == 0) {
    printf("Testing\n");
    if (check()) {
      printf("PASSED\n");
      return 0;
    } else {
      printf("FAILED\n");
      return 1;
    }
  } else if (strcmp(argv[1], "--checksum") == 0) {
    printf("Calculating checksum\n");
    init();
    kernel();
    checksum();
    return 0;
  } else {
    printf("Unsupported command %s\n", argv[1]);
    return 1;
  }
}

