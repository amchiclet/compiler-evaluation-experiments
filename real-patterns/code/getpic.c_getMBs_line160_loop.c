#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int mb_height;
extern int k;
extern int  MV[2][5][72 + 1][88 + 2] ;
extern int mb_width;
extern int  modemap[72 + 1][88 + 2] ;

void loop()
{
#pragma scop

    for(i = 0; i < mb_height + 1; i++)
    {
        for(k = 0; k < 5; k++)
        {
            MV[0][k][i][0] = 0;
            MV[1][k][i][0] = 0;
            MV[0][k][i][mb_width + 1] = 0;
            MV[1][k][i][mb_width + 1] = 0;
        }
        modemap[i][0] = 3;
        modemap[i][mb_width + 1] = 3;
    }

#pragma endscop
}
