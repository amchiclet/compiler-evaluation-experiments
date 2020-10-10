#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern long k;
extern long Inner_loops;
extern double  Sumcheck[3][25] ;
extern long Section;
extern double  Vxne[101] ;
extern double  Vxnd[101] ;

void loop()
{
#pragma scop

    for(k = 0; k < Inner_loops; k++)
    {
        Sumcheck[Section][17] = Sumcheck[Section][17] +(Vxne[k] + Vxnd[k]) *((double )(k + 1));
    }

#pragma endscop
}
