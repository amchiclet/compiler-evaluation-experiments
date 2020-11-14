#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int * restrict tonelabel;
extern double  Xtm[513] ;
extern double  power[513] ;
extern int  maxima[513] ;

void loop()
{
#pragma scop

    for(i = 1; i < 513 - 1; i++)
    {
        tonelabel[i] = 0;
        Xtm[i] = - 200.0;
        if(power[i] > power[i - 1] && power[i] > power[i + 1]) maxima[i] = 1;
        else maxima[i] = 0;
    }

#pragma endscop
}
