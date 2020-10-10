#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int k;
extern int i;
extern int n;
extern double * restrict c;
extern double* restrict lambda;
extern double* restrict x;

void loop()
{
#pragma scop

    for(j = 0; j < k; j++)
    {
        for(i = 0; i < n; i++)
        {
            c[i + j * n] = c[i + j * n] - lambda[j] * x[i + j * n];
        }
    }

#pragma endscop
}
