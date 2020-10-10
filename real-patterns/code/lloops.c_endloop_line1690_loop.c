#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern long k;
extern long Inner_loops;
extern long j;
extern long m;
extern double  Sumcheck[3][25] ;
extern long Section;
extern double  P[512][4] ;

void loop()
{
#pragma scop

    for(k = 0; k < 2 * Inner_loops; k++)
    {
        for(j = 0; j < 4; j++)
        {
            m = 4 * k + j + 1;
            Sumcheck[Section][13] = Sumcheck[Section][13] + P[k][j] *((double )m);
        }
    }

#pragma endscop
}
