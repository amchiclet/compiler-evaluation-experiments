#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
extern double  x[2000 + 0] ;
extern double  y[2000 + 0] ;
extern double  b[2000 + 0] ;
extern double fn;

void loop()
{
#pragma scop

    for(i = 0; i < n; i++)
    {
        x[i] = 0;
        y[i] = 0;
        b[i] =(i + 1) / fn / 2.0 + 4;
    }

#pragma endscop
}
