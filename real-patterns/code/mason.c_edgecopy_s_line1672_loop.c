#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int  mor_s_v[2][4] ;
extern int  idmo[2400][6][2][2][5][5] ;
extern int ntemp1;
extern int  jjface[6] ;
extern int face;

void loop()
{
#pragma scop

    for(i = 1; i < 5 - 1; i++)
    {
        mor_s_v[0][i - 1] = idmo[ntemp1][jjface[face]][0][0][i][0];
    }

#pragma endscop
}
