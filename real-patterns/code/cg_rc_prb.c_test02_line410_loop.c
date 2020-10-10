#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
extern double * restrict z;
extern double * restrict r;
extern double * restrict a;

void loop()
{
#pragma scop

    for(i = 0; i < n; i++)
    {
        z[i] = r[i] / a[i + i * n];
    }

#pragma endscop
}
