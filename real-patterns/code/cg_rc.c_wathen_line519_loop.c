#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int n;
extern int i;
extern double * restrict a;

void loop()
{
#pragma scop

    for(j = 0; j < n; j++)
    {
        for(i = 0; i < n; i++)
        {
            a[i + j * n] = 0.0;
        }
    }

#pragma endscop
}
