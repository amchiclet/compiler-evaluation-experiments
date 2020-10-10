#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int k;
extern int i;
extern int n;
extern double * restrict c;
extern int l;
extern double* restrict a;
extern double* restrict x;

void loop()
{
#pragma scop

    for(j = 0; j < k; j++)
    {
        for(i = 0; i < n; i++)
        {
            c[i + j * n] = 0.0;
            for(l = 0; l < n; l++)
            {
                c[i + j * n] = c[i + j * n] + a[i + l * n] * x[l + j * n];
            }
        }
    }

#pragma endscop
}
