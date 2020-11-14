#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int column;
extern int NNWIDTH;
extern int ** restrict vectors;
extern int vec;
extern int vpos;
extern char * restrict srow;

void loop()
{
#pragma scop

    for(column = 0; column < NNWIDTH; column++)
    {
        vectors[vec][vpos] =(srow[column] == 'X'?1 : - 1);
        vpos++;
    }

#pragma endscop
}
