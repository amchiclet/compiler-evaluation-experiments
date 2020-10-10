#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern long k;
extern long Inner_loops;
extern double  Sumcheck[3][25] ;
extern long Section;
extern double  Xx[1001] ;

void loop()
{
#pragma scop

    for(k = 1; k < Inner_loops + 1; k++)
    {
        Sumcheck[Section][20] = Sumcheck[Section][20] + Xx[k] *((double )k);
    }

#pragma endscop
}
