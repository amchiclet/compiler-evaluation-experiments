#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
extern double * restrict x;

void loop()
{
#pragma scop

    for(i = 0; i < n; i++)
    {
        x[i] = 0.0;
    }

#pragma endscop
}
