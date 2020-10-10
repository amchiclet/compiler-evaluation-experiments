#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
extern double* restrict x;
typedef int boolean;
extern int* restrict mark;

void loop()
{
#pragma scop

    for(i = 1; i <= n; i++)
    {
        x[i] = 0.0;
        mark[i] = 0;
    }

#pragma endscop
}
