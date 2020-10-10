#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int lastcol;
extern int firstcol;
extern double d;
extern double* restrict x;
extern double* restrict r;
extern double sum;

void loop()
{
#pragma scop

    for(j = 1; j <= lastcol - firstcol + 1; j++)
    {
        d = x[j] - r[j];
        sum = sum + d * d;
    }

#pragma endscop
}
