#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int m;
extern double* restrict ax;
extern int j;
extern int n;
extern double* restrict a;
extern double* restrict x;

void loop()
{
#pragma scop

    for(i = 0; i < m; i++)
    {
        ax[i] = 0.0;
        for(j = 0; j < n; j++)
        {
            ax[i] = ax[i] + a[i + j * m] * x[j];
        }
    }

#pragma endscop
}
