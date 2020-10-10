#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
extern int m;
extern double  errnm[5] ;
extern int nx0;
extern int ny0;
extern int nz0;

void loop()
{
#pragma scop

    for(m = 0; m < 5; m++)
    {
        errnm[m] = sqrt(errnm[m] /((nx0 - 2) *(ny0 - 2) *(nz0 - 2)));
    }

#pragma endscop
}
