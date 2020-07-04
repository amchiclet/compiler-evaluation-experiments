// When compiled with gcc -O2 -O3 they produce the same checksum
// When compiled with gcc -Ofast, they produce a different checksum
#include <x86intrin.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <limits.h>
#include <string.h>

float (*A)[11180][11180];
float (*B)[11180][11180];

float frand(float min, float max) {
  float scale = rand() / (float) RAND_MAX;
  return min + scale * (max - min);
}


float irand(int min, int max) {
  return min + (rand() % (max - min));
}

void init() {
  A = malloc(sizeof(float) * 11180 * 11180);
  for (int i = 0;i < 11180;++i) {
    for (int j = 0;j < 11180;++j) {
      float v = frand(0.0, 1.0);
      (*A)[i][j] = v;
    }
  }
  B = malloc(sizeof(float) * 11180 * 11180);
  for (int i = 0;i < 11180;++i) {
    for (int j = 0;j < 11180;++j) {
      float v = frand(0.0, 1.0);
      (*B)[i][j] = v;
    }
  }
}
clock_t kernel() {
  clock_t before = clock();
    for (int i = 1; i < 11180; ++i) {
      for (int j = 1; j < 11180; ++j) {
        (*A)[i][j] = (*A)[i - 1][j - 1] * (*B)[i][j];
      }
    }
  clock_t after = clock();
  return after - before;
}
int check() {
  int (*A_ref)[11180][11180];
  int (*A_test)[11180][11180];
  int (*B_ref)[11180][11180];
  int (*B_test)[11180][11180];
  // Initialization
  A_ref = malloc(sizeof(int) * 11180 * 11180);
  A_test = malloc(sizeof(int) * 11180 * 11180);
  for (int i = 0;i < 11180;++i) {
    for (int j = 0;j < 11180;++j) {
      int v = irand(1, 10);
      (*A_ref)[i][j] = v;
      (*A_test)[i][j] = v;
    }
  }
  B_ref = malloc(sizeof(int) * 11180 * 11180);
  B_test = malloc(sizeof(int) * 11180 * 11180);
  for (int i = 0;i < 11180;++i) {
    for (int j = 0;j < 11180;++j) {
      int v = irand(1, 10);
      (*B_ref)[i][j] = v;
      (*B_test)[i][j] = v;
    }
  }
  // Test program
  for (int i = 1; i < 11180; ++i) {
    for (int j = 1; j < 11180; ++j) {
      (*A_test)[i][j] = (*A_test)[i - 1][j - 1] * (*B_test)[i][j];
    }
  }
  // Reference program
  for (int j = 1; j < 11180; ++j) {
    for (int i = 1; i < 11180; ++i) {
      (*A_ref)[i][j] = (*A_ref)[i - 1][j - 1] * (*B_ref)[i][j];
    }
  }
  // Compare the results
  for (int i = 0;i < 11180;++i) {
    for (int j = 0;j < 11180;++j) {
      if ((*A_test)[i][j] != (*A_ref)[i][j]) return 0;
    }
  }
  for (int i = 0;i < 11180;++i) {
    for (int j = 0;j < 11180;++j) {
      if ((*B_test)[i][j] != (*B_ref)[i][j]) return 0;
    }
  }
  return 1;
}
void checksum() {
  float total = 0.0;
  for (int i = 0;i < 11180;++i) {
    for (int j = 0;j < 11180;++j) {
      total += (*B)[i][j];
    }
  }
  for (int i = 0;i < 11180;++i) {
    for (int j = 0;j < 11180;++j) {
      total += (*A)[i][j];
    }
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

