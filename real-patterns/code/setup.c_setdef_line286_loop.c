#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int j;
extern int ip;
extern double  wdtdr[5][5] ;
extern double  wxm1[5] ;
extern double  dxm1[5][5] ;

void loop()
{
#pragma scop

    for(i = 0; i < 5; i++)
    {
        for(j = 0; j < 5; j++)
        {
            for(ip = 0; ip < 5; ip++)
            {
                wdtdr[j][i] = wdtdr[j][i] + wxm1[ip] * dxm1[i][ip] * dxm1[j][ip];
            }
        }
    }

#pragma endscop
}
