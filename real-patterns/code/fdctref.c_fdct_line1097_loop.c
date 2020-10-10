#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int j;
extern double s;
extern int k;
extern double  c[8][8] ;
extern short * restrict block;
extern double  tmp[64] ;

void loop()
{
#pragma scop

    for(i = 0; i < 8; i++)
    {
        for(j = 0; j < 8; j++)
        {
            s = 0.0;
            for(k = 0; k < 8; k++) s += c[j][k] * block[8 * i + k];
            tmp[8 * i + j] = s;
        }
    }

#pragma endscop
}
