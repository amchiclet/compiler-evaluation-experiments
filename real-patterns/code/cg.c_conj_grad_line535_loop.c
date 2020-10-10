#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int lastrow;
extern int firstrow;
extern double d;
extern int k;
extern int* restrict rowstr;
extern double* restrict a;
extern double* restrict z;
extern int* restrict colidx;
extern double* restrict w;
extern double* restrict r;

void loop()
{
#pragma scop

    for(j = 1; j <= lastrow - firstrow + 1; j++)
    {
        d = 0.0;
        for(k = rowstr[j]; k <= rowstr[j + 1] - 1; k++)
        {
            d = d + a[k] * z[colidx[k]];
        }
        w[j] = d;
        r[j] = d;
    }

#pragma endscop
}
