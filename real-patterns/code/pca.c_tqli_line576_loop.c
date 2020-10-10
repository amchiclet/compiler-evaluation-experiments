#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
extern float* restrict e;

void loop()
{
#pragma scop

    for(i = 2; i <= n; i++) e[i - 1] = e[i];

#pragma endscop
}
