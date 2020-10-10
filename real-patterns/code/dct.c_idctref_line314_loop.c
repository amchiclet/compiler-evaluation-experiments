#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int j;
extern double partial_product;
extern int k;
extern double  c[8][8] ;
extern int  tmp2[64] ;
extern double  tmp[64] ;

void loop()
{
#pragma scop

    for(i = 0; i < 8; i++) for(j = 0; j < 8; j++)
        {
            partial_product = 0.0;
            for(k = 0; k < 8; k++) partial_product += c[k][j] * tmp2[8 * i + k];
            tmp[8 * i + j] = partial_product;
        }

#pragma endscop
}
