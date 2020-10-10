#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern long i;
extern long j;
extern double  Px0[101][25] ;
extern double  Px[101][25] ;

void loop()
{
#pragma scop

    for(i = 0; i < 101; i++)
    {
        for(j = 0; j < 25; j++)
        {
            Px0[i][j] = Px[i][j];
        }
    }

#pragma endscop
}
