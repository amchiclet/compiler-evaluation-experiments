#include <x86intrin.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <limits.h>
#include <string.h>

#include "util/init.h"
#include "test/naive_impl.h"
#include "test/ulp.h"
#include "argparse/argparse.h"

typedef float Array3D[500][500][500];
Array3D * restrict A = NULL;
Array3D * restrict B = NULL;
Array3D * restrict C = NULL;
Array3D * restrict Atest = NULL;
Array3D * restrict Btest = NULL;
Array3D * restrict Ctest = NULL;

void init() {
  printf("Initializing\n");
  srand(0);
  A = malloc(sizeof(Array3D));
  B = malloc(sizeof(Array3D));
  C = malloc(sizeof(Array3D));
  Atest = malloc(sizeof(Array3D));
  Btest = malloc(sizeof(Array3D));
  Ctest = malloc(sizeof(Array3D));
  init_3d((float*)A, 500, 500, 500);
  init_3d((float*)B, 500, 500, 500);
  init_3d((float*)C, 500, 500, 500);
  copy_3d((float*)A, (float*)Atest, 500, 500, 500);
  copy_3d((float*)B, (float*)Btest, 500, 500, 500);
  copy_3d((float*)C, (float*)Ctest, 500, 500, 500);
}

clock_t kernel() {
  clock_t before = clock();
  for (int i_0 = 1; i_0 < 499; ++i_0) {
    for (int i_1 = 1; i_1 < 499; ++i_1) {
      for (int i_2 = 1; i_2 < 5; ++i_2) {
        (*B)[i_0][i_1][i_2] = ((*A)[(i_0 + 1)][(i_1 + 1)][i_2] * (*B)[(i_0 + 1)][i_1][i_2]);
      }
      for (int i_2 = 5; i_2 < 485; i_2+=30) {
        (*B)[i_0][i_1][(i_2 + 0)] = ((*A)[(i_0 + 1)][(i_1 + 1)][(i_2 + 0)] * (*B)[(i_0 + 1)][i_1][(i_2 + 0)]);
        (*B)[i_0][i_1][(i_2 + 1)] = ((*A)[(i_0 + 1)][(i_1 + 1)][(i_2 + 1)] * (*B)[(i_0 + 1)][i_1][(i_2 + 1)]);
        (*B)[i_0][i_1][(i_2 + 2)] = ((*A)[(i_0 + 1)][(i_1 + 1)][(i_2 + 2)] * (*B)[(i_0 + 1)][i_1][(i_2 + 2)]);
        (*B)[i_0][i_1][(i_2 + 3)] = ((*A)[(i_0 + 1)][(i_1 + 1)][(i_2 + 3)] * (*B)[(i_0 + 1)][i_1][(i_2 + 3)]);
        (*B)[i_0][i_1][(i_2 + 4)] = ((*A)[(i_0 + 1)][(i_1 + 1)][(i_2 + 4)] * (*B)[(i_0 + 1)][i_1][(i_2 + 4)]);
        (*B)[i_0][i_1][(i_2 + 5)] = ((*A)[(i_0 + 1)][(i_1 + 1)][(i_2 + 5)] * (*B)[(i_0 + 1)][i_1][(i_2 + 5)]);
        (*B)[i_0][i_1][(i_2 + 6)] = ((*A)[(i_0 + 1)][(i_1 + 1)][(i_2 + 6)] * (*B)[(i_0 + 1)][i_1][(i_2 + 6)]);
        (*B)[i_0][i_1][(i_2 + 7)] = ((*A)[(i_0 + 1)][(i_1 + 1)][(i_2 + 7)] * (*B)[(i_0 + 1)][i_1][(i_2 + 7)]);
        (*B)[i_0][i_1][(i_2 + 8)] = ((*A)[(i_0 + 1)][(i_1 + 1)][(i_2 + 8)] * (*B)[(i_0 + 1)][i_1][(i_2 + 8)]);
        (*B)[i_0][i_1][(i_2 + 9)] = ((*A)[(i_0 + 1)][(i_1 + 1)][(i_2 + 9)] * (*B)[(i_0 + 1)][i_1][(i_2 + 9)]);
        (*B)[i_0][i_1][(i_2 + 10)] = ((*A)[(i_0 + 1)][(i_1 + 1)][(i_2 + 10)] * (*B)[(i_0 + 1)][i_1][(i_2 + 10)]);
        (*B)[i_0][i_1][(i_2 + 11)] = ((*A)[(i_0 + 1)][(i_1 + 1)][(i_2 + 11)] * (*B)[(i_0 + 1)][i_1][(i_2 + 11)]);
        (*B)[i_0][i_1][(i_2 + 12)] = ((*A)[(i_0 + 1)][(i_1 + 1)][(i_2 + 12)] * (*B)[(i_0 + 1)][i_1][(i_2 + 12)]);
        (*B)[i_0][i_1][(i_2 + 13)] = ((*A)[(i_0 + 1)][(i_1 + 1)][(i_2 + 13)] * (*B)[(i_0 + 1)][i_1][(i_2 + 13)]);
        (*B)[i_0][i_1][(i_2 + 14)] = ((*A)[(i_0 + 1)][(i_1 + 1)][(i_2 + 14)] * (*B)[(i_0 + 1)][i_1][(i_2 + 14)]);
        (*B)[i_0][i_1][(i_2 + 15)] = ((*A)[(i_0 + 1)][(i_1 + 1)][(i_2 + 15)] * (*B)[(i_0 + 1)][i_1][(i_2 + 15)]);
        (*B)[i_0][i_1][(i_2 + 16)] = ((*A)[(i_0 + 1)][(i_1 + 1)][(i_2 + 16)] * (*B)[(i_0 + 1)][i_1][(i_2 + 16)]);
        (*B)[i_0][i_1][(i_2 + 17)] = ((*A)[(i_0 + 1)][(i_1 + 1)][(i_2 + 17)] * (*B)[(i_0 + 1)][i_1][(i_2 + 17)]);
        (*B)[i_0][i_1][(i_2 + 18)] = ((*A)[(i_0 + 1)][(i_1 + 1)][(i_2 + 18)] * (*B)[(i_0 + 1)][i_1][(i_2 + 18)]);
        (*B)[i_0][i_1][(i_2 + 19)] = ((*A)[(i_0 + 1)][(i_1 + 1)][(i_2 + 19)] * (*B)[(i_0 + 1)][i_1][(i_2 + 19)]);
        (*B)[i_0][i_1][(i_2 + 20)] = ((*A)[(i_0 + 1)][(i_1 + 1)][(i_2 + 20)] * (*B)[(i_0 + 1)][i_1][(i_2 + 20)]);
        (*B)[i_0][i_1][(i_2 + 21)] = ((*A)[(i_0 + 1)][(i_1 + 1)][(i_2 + 21)] * (*B)[(i_0 + 1)][i_1][(i_2 + 21)]);
        (*B)[i_0][i_1][(i_2 + 22)] = ((*A)[(i_0 + 1)][(i_1 + 1)][(i_2 + 22)] * (*B)[(i_0 + 1)][i_1][(i_2 + 22)]);
        (*B)[i_0][i_1][(i_2 + 23)] = ((*A)[(i_0 + 1)][(i_1 + 1)][(i_2 + 23)] * (*B)[(i_0 + 1)][i_1][(i_2 + 23)]);
        (*B)[i_0][i_1][(i_2 + 24)] = ((*A)[(i_0 + 1)][(i_1 + 1)][(i_2 + 24)] * (*B)[(i_0 + 1)][i_1][(i_2 + 24)]);
        (*B)[i_0][i_1][(i_2 + 25)] = ((*A)[(i_0 + 1)][(i_1 + 1)][(i_2 + 25)] * (*B)[(i_0 + 1)][i_1][(i_2 + 25)]);
        (*B)[i_0][i_1][(i_2 + 26)] = ((*A)[(i_0 + 1)][(i_1 + 1)][(i_2 + 26)] * (*B)[(i_0 + 1)][i_1][(i_2 + 26)]);
        (*B)[i_0][i_1][(i_2 + 27)] = ((*A)[(i_0 + 1)][(i_1 + 1)][(i_2 + 27)] * (*B)[(i_0 + 1)][i_1][(i_2 + 27)]);
        (*B)[i_0][i_1][(i_2 + 28)] = ((*A)[(i_0 + 1)][(i_1 + 1)][(i_2 + 28)] * (*B)[(i_0 + 1)][i_1][(i_2 + 28)]);
        (*B)[i_0][i_1][(i_2 + 29)] = ((*A)[(i_0 + 1)][(i_1 + 1)][(i_2 + 29)] * (*B)[(i_0 + 1)][i_1][(i_2 + 29)]);
      }
      for (int i_2 = 485; i_2 < 499; ++i_2) {
        (*B)[i_0][i_1][i_2] = ((*A)[(i_0 + 1)][(i_1 + 1)][i_2] * (*B)[(i_0 + 1)][i_1][i_2]);
      }
    }
  }
  clock_t after = clock();
  return after - before;
}

void run(int n_iterations, const char* runtime_log_path) {
  // assuming micro seconds
  if (CLOCKS_PER_SEC != 1000000) {
    printf("WARNING: CLOCK_PER_SEC=%d. Expected micro seconds (1000000).", CLOCKS_PER_SEC);
  }

  int *runtimes = (int*)malloc(n_iterations * sizeof(int));

  for (int i = 0; i < n_iterations; ++i) {
    runtimes[i] = (int)kernel();
  }

  // Log runtimes
  FILE *f;
  f = fopen(runtime_log_path, "w");
  assert(f != NULL);
  for (int i = 0; i < n_iterations; ++i) {
    fprintf(f, "iteration %d %d\n", i+1, runtimes[i]);
  }
  fclose(f);
  free(runtimes);
}

void check() {
  printf("Checking\n");
  // Largest number is produced by 1.0 + 1.0 twice
  float largest_number = 4.0;
  float largest_ulp = ulp(largest_number);
  printf("largest number %f ulp %.30f\n", largest_number, largest_ulp);
  // Only one operation on the right handside
  size_t n_ops = 1;
  float tolerance = largest_ulp * n_ops / 2;
  printf("tolerance is %.30f\n", tolerance);
  for (int i_0 = 1; i_0 < 499; ++i_0) {
    for (int i_1 = 1; i_1 < 499; ++i_1) {
      for (int i_2 = 1; i_2 < 499; ++i_2) {
        (*Btest)[i_0][i_1][i_2] = ((*Atest)[(i_0 + 1)][(i_1 + 1)][i_2] * (*Btest)[(i_0 + 1)][i_1][i_2]);
      }
    }
  }
  int pass = 1;
  pass = pass && compare_3d((float*)A, (float*)Atest, 1, 499, 500, 1, 499, 500, 1, 499, 500, tolerance);
  pass = pass && compare_3d((float*)B, (float*)Btest, 1, 499, 500, 1, 499, 500, 1, 499, 500, tolerance);
  pass = pass && compare_3d((float*)C, (float*)Ctest, 1, 499, 500, 1, 499, 500, 1, 499, 500, tolerance);
  printf(pass ? "PASS\n" : "FAIL\n");
}

static const char *const usage[] = {
    "program_name --n_iterations N --runtime_log_path P [--check_correctness]",
    NULL,
};

int main(int argc, const char *argv[]) {
  int check_correctness = 0;
  int n_iterations = 1;
  const char *runtime_log_path = NULL;

  struct argparse_option options[] = {
    OPT_HELP(),
    OPT_GROUP("Options"),
    OPT_INTEGER('n', "n_iterations", &n_iterations, "number of iterations"),
    OPT_STRING('o', "runtime_log_path", &runtime_log_path, "path to log runtime"),
    OPT_BOOLEAN('c', "check_correctness", &check_correctness, "check for correctness (only applicable if run for 1 iteration)"),
    OPT_END(),
  };

  struct argparse argparse;
  argparse_init(&argparse, options, usage, 0);
  argparse_describe(&argparse, "\nA brief description of what the program does and how it works.", "\nAdditional description of the program after the description of the arguments.");
  argc = argparse_parse(&argparse, argc, argv);

  printf("argc = %d\n", argc);
  printf("iterations = %d\n", n_iterations);
  printf("runtime log path = %s\n", runtime_log_path);

  assert(n_iterations > 0);
  assert(runtime_log_path != NULL);

  printf("Initializing\n");
  init();

  printf("Running\n");
  run(n_iterations, runtime_log_path);

  if (check_correctness) {
    if (n_iterations != 1) {
      printf("Bypassing correctness checking because # of iterations is not 1.\n");
    } else {
      check();
    }
  }
  return 0;
}