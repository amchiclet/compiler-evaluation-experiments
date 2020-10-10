#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
extern int j;
extern double * restrict A;
extern double * restrict D;

void loop()
{
#pragma scop

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++) A[n * i + j] = A[n * i + j] / sqrt(D[i]) / sqrt(D[j]);
    }

#pragma endscop
}
