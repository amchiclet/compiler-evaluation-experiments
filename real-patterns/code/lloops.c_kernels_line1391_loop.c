#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern long k;
extern long Inner_loops;
extern double  B5[101] ;
extern long kb5i;
extern double  Sa[101] ;
extern double  Xtra[40] ;
extern double  Sb[101] ;

void loop()
{
#pragma scop

    for(k = 0; k < Inner_loops; k++)
    {
        B5[k + kb5i] = Sa[k] + Xtra[35] * Sb[k];
        Xtra[35] = B5[k + kb5i] - Xtra[35];
    }

#pragma endscop
}
