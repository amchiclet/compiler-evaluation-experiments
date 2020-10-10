#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
extern int j;
extern double * restrict D;
extern double * restrict A;

void loop()
{
#pragma scop

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++) D[i] += -A[n * i + j];
        A[n * i + i] = D[i];
    }

#pragma endscop
}
