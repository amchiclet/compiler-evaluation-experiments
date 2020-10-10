#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern long k;
extern long Inner_loops;
extern long i;
extern long m;
extern double  Sumcheck[3][25] ;
extern long Section;
extern double  Px[101][25] ;

void loop()
{
#pragma scop

    for(k = 0; k < Inner_loops; k++)
    {
        for(i = 0; i < 25; i++)
        {
            m = 25 * k + i + 1;
            Sumcheck[Section][21] = Sumcheck[Section][21] + Px[k][i] *((double )m);
        }
    }

#pragma endscop
}
