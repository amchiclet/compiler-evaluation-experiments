#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
extern double* restrict v;
extern double* restrict a;

void loop()
{
#pragma scop

    for(i = 0; i < n; i++)
    {
        v[i] = a[i + i * n];
    }

#pragma endscop
}
