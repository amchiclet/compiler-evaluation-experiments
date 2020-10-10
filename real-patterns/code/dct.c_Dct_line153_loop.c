#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int j;
extern int * restrict coeff;
extern int  zigzag[8][8] ;
extern float  d[8][8] ;

void loop()
{
#pragma scop

    for(i = 0; i < 8; i++)
    {
        for(j = 0; j < 8; j++)
        {
            *(coeff + zigzag[i][j]) =((int )d[i][j]);
        }
    }

#pragma endscop
}
