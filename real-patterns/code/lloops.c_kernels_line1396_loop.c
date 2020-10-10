#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern long i;
extern long Inner_loops;
extern long k;
extern double  B5[101] ;
extern long kb5i;
extern double  Sa[101] ;
extern double  Xtra[40] ;
extern double  Sb[101] ;

void loop()
{
#pragma scop

    for(i = 1; i <= Inner_loops; i++)
    {
        k = Inner_loops - i;
        B5[k + kb5i] = Sa[k] + Xtra[35] * Sb[k];
        Xtra[35] = B5[k + kb5i] - Xtra[35];
    }

#pragma endscop
}
