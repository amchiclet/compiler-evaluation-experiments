#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern long k;
extern long Inner_loops;
extern double  Sumcheck[3][25] ;
extern long Section;
extern double  X[1001] ;

void loop()
{
#pragma scop

    for(k = 1; k < Inner_loops; k++)
    {
        Sumcheck[Section][5] = Sumcheck[Section][5] + X[k] *((double )k);
    }

#pragma endscop
}
