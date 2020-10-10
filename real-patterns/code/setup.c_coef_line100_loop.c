#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
extern int j;
extern int i;
extern double  w3m1[5][5][5] ;
extern double  wxm1[5] ;

void loop()
{
#pragma scop

    for(k = 0; k < 5; k++)
    {
        for(j = 0; j < 5; j++)
        {
            for(i = 0; i < 5; i++)
            {
                w3m1[k][j][i] = wxm1[i] * wxm1[j] * wxm1[k];
            }
        }
    }

#pragma endscop
}
