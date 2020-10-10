#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int iy;
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

    for(iy = 0; iy < 5; iy++)
    {
        for(ix = 0; ix < 5; ix++)
        {
            y[0][iy][ix] = x1[0][iy][ix];
            y[1][iy][ix] = 0.0;
            for(ip = 0; ip < 5; ip++)
            {
                y[1][iy][ix] = y[1][iy][ix] + map2[ip] * x1[ip][iy][ix];
            }
            y[2][iy][ix] = x1[5 - 1][iy][ix];
            y[3][iy][ix] = 0.0;
            for(ip = 0; ip < 5; ip++)
            {
                y[3][iy][ix] = y[3][iy][ix] + map4[ip] * x2[ip][iy][ix];
            }
            y[5 - 1][iy][ix] = x2[5 - 1][iy][ix];
        }
    }

#pragma endscop
}
