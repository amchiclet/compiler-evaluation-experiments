#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int iz;
extern int ix;
extern double  y[5][5][5] ;
extern double  x1[5][5][5] ;
extern int ip;
extern double  map2[5] ;
extern double  map4[5] ;
extern double  x2[5][5][5] ;

void loop()
{
#pragma scop

    for(iz = 0; iz < 5; iz++)
    {
        for(ix = 0; ix < 5; ix++)
        {
            y[iz][0][ix] = x1[iz][0][ix];
            y[iz][1][ix] = 0.0;
            for(ip = 0; ip < 5; ip++)
            {
                y[iz][1][ix] = y[iz][1][ix] + map2[ip] * x1[iz][ip][ix];
            }
            y[iz][2][ix] = x1[iz][5 - 1][ix];
            y[iz][3][ix] = 0.0;
            for(ip = 0; ip < 5; ip++)
            {
                y[iz][3][ix] = y[iz][3][ix] + map4[ip] * x2[iz][ip][ix];
            }
            y[iz][5 - 1][ix] = x2[iz][5 - 1][ix];
        }
    }

#pragma endscop
}
