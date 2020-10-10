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

    for(k = 0; k < Inner_loops; k++)
    {
        Sumcheck[Section][1] = Sumcheck[Section][1] + X[k] *((double )(k + 1));
    }

#pragma endscop
}
