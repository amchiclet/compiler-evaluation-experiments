#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
extern double * restrict c;

void loop()
{
#pragma scop

    for(i = 0; i < n; i++)
    {
        c[i] = 2.0 * c[i] /((double )n);
    }

#pragma endscop
}
