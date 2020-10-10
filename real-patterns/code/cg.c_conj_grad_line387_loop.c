#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int lastcol;
extern int firstcol;
extern double* restrict x;
extern double rho;

void loop()
{
#pragma scop

    for(j = 1; j <= lastcol - firstcol + 1; j++)
    {
        double xj = x[j];
        rho = rho + xj * xj;
    }

#pragma endscop
}
