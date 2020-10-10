#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern long k;
extern long Inner_loops;
extern double  Sumcheck[3][25] ;
extern long Section;
extern double  B5[101] ;

void loop()
{
#pragma scop

    for(k = 0; k < Inner_loops; k++)
    {
        Sumcheck[Section][19] = Sumcheck[Section][19] + B5[k] *((double )(k + 1));
    }

#pragma endscop
}
