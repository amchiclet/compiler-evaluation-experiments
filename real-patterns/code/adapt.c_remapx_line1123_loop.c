#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int iz;
extern int iy;
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
        for(iy = 0; iy < 5; iy++)
        {
            y[iz][iy][0] = x1[iz][iy][0];
            y[iz][iy][1] = 0.0;
            for(ip = 0; ip < 5; ip++)
            {
                y[iz][iy][1] = y[iz][iy][1] + map2[ip] * x1[iz][iy][ip];
            }
            y[iz][iy][2] = x1[iz][iy][5 - 1];
            y[iz][iy][3] = 0.0;
            for(ip = 0; ip < 5; ip++)
            {
                y[iz][iy][3] = y[iz][iy][3] + map4[ip] * x2[iz][iy][ip];
            }
            y[iz][iy][5 - 1] = x2[iz][iy][5 - 1];
        }
    }

#pragma endscop
}
