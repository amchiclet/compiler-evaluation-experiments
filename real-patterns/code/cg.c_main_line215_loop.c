#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int lastcol;
extern int firstcol;
extern double  z[14000 + 2 + 1] ;
extern double norm_temp11;
extern double  x[14000 + 2 + 1] ;
extern double norm_temp12;

void loop()
{
#pragma scop

    for(j = 1; j <= lastcol - firstcol + 1; j++)
    {
        double zj = z[j];
        norm_temp11 = norm_temp11 + x[j] * zj;
        norm_temp12 = norm_temp12 + zj * zj;
    }

#pragma endscop
}
