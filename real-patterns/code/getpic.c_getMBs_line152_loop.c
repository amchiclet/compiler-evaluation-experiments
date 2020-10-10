#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int mb_width;
extern int k;
extern int  MV[2][5][72 + 1][88 + 2] ;
extern int  modemap[72 + 1][88 + 2] ;

void loop()
{
#pragma scop

    for(i = 1; i < mb_width + 1; i++)
    {
        for(k = 0; k < 5; k++)
        {
            MV[0][k][0][i] = 999;
            MV[1][k][0][i] = 999;
        }
        modemap[0][i] = 3;
    }

#pragma endscop
}
