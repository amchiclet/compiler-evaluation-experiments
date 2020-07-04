#include <stdio.h>
#include <time.h>

void dummy2(float *a, float *b);

#define LEN 32000
#define N_ITERATIONS 400000

//__attribute__ ((aligned(16)))
float X[32000], Y[32000];

void init() {
  for (int i = 0; i < LEN; ++i) {
    X[i] = 1 + i;
    Y[i] = 2 + i;
  }
}

void check() {
  float sumx = 0;
  for (int i = 0; i < LEN; ++i) {
    sumx += X[i];
  }
  printf("%f \n", sumx);
}

int main(int argc, char* argv[]) {
  init();

  clock_t start_t = clock();
  for (int n = 0; n < N_ITERATIONS; ++n) {
    #pragma @ICE loop=l1
		for (int i = 0; i < LEN; i++) {
			X[i] = Y[i] + 1;
		}
		dummy2(&X[0], &Y[0]);
	}
	clock_t end_t = clock();

  clock_t clock_dif = end_t - start_t;
	double clock_dif_sec = (double) (clock_dif/1000000.0);

	printf("%s\t %.2f \t\t", argv[0], clock_dif_sec);

	check();
	return 0;
}
