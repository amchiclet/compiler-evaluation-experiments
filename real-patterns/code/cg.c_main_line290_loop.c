#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int lastcol;
extern int firstcol;
extern double  x[14000 + 2 + 1] ;
extern double norm_temp12;
extern double  z[14000 + 2 + 1] ;

void loop()
{
#pragma scop

    for(j = 1; j <= lastcol - firstcol + 1; j++)
    {
        x[j] = norm_temp12 * z[j];
    }

#pragma endscop
}
