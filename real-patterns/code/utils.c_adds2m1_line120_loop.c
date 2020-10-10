#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
extern double* restrict a;
extern double c1;
extern double* restrict b;

void loop()
{
#pragma scop

    for(i = 0; i < n; i++)
    {
        a[i] = a[i] + c1 * b[i];
    }

#pragma endscop
}
