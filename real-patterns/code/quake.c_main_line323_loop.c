#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int  cor[4] ;
extern int ** restrict ARCHvertex;
extern int i;

void loop()
{
#pragma scop

    for(j = 0; j < 4; j++)
    {
        cor[j] = ARCHvertex[i][j];
    }

#pragma endscop
}
