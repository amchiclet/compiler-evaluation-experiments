#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
extern int j;
typedef int32_t od_coeff;
extern od_coeff  refout[1 << 6][1 << 6] ;
typedef int int32_t;
extern double  floatcoefs[1 << 6][1 << 6] ;

void loop()
{
#pragma scop

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            refout[i][j] =((od_coeff )(floor(floatcoefs[i][j] + 0.5)));
            refout[i][j] = - 256 ^(- 256 ^(refout[i][j] ^(255 ^ refout[i][j]) & -(255 < refout[i][j]))) & -((refout[i][j] ^(255 ^ refout[i][j]) & -(255 < refout[i][j])) > - 256);
        }
    }

#pragma endscop
}
