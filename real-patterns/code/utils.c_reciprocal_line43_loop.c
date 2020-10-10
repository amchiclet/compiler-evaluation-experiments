#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
extern double* restrict a;

void loop()
{
#pragma scop

    for(i = 0; i < n; i++)
    {
        a[i] = 1.0 / a[i];
    }

#pragma endscop
}
