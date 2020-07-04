#include <stdio.h>
#include <time.h>
int dummy_2(void *a, void *b);
float X[32000];
float Y[32000];
void init()
{
  for (int i = 0; i < 32000; ++i)
  {
    X[i] = 1 + i;
    Y[i] = 2 + i;
  }

}

void check()
{
  float sumx = 0;
  for (int i = 0; i < 32000; ++i)
  {
    sumx += X[i];
  }

  printf("%f \n", sumx);
}

int main(int argc, char *argv[])
{
  int i;
  init();
  clock_t start_t = clock();
  for (int n = 0; n < 400000; ++n)
  {
    #pragma @ICE loop=l1
    for (i = 0; i <= 31999; i += 8)
    {
      X[i] = Y[i] + 1;
      X[i + 1] = Y[i + 1] + ((float) 1);
      X[i + 2] = Y[i + 2] + ((float) 1);
      X[i + 3] = Y[i + 3] + ((float) 1);
      X[i + 4] = Y[i + 4] + ((float) 1);
      X[i + 5] = Y[i + 5] + ((float) 1);
      X[i + 6] = Y[i + 6] + ((float) 1);
      X[i + 7] = Y[i + 7] + ((float) 1);
    }

    dummy_2(&X[0], &Y[0]);
  }

  clock_t end_t = clock();
  clock_t clock_dif = end_t - start_t;
  double clock_dif_sec = (double) (clock_dif / 1000000.0);
  printf("%s\t %.2f \t\t", argv[0], clock_dif_sec);
  check();
  return 0;
}

