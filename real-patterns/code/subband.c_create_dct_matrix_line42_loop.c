#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int k;
extern double  filter[16][32] ;

void loop()
{
#pragma scop

    for(i = 0; i < 16; i++) for(k = 0; k < 32; k++)
        {
            if((filter[i][k] = 1e9 * cos(((double )(((2 * i + 1) * k) * 3.14159265358979 / 64)))) >= 0) modf(filter[i][k] + 0.5,&filter[i][k]);
            else modf(filter[i][k] - 0.5,&filter[i][k]);
            filter[i][k] *= 1e-9;
        }

#pragma endscop
}
