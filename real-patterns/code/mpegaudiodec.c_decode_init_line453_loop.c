#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int j;
extern int32_t  mdct_win[8][36] ;

void loop()
{
#pragma scop

    for(i = 0; i < 36; i++)
    {
        for(j = 0; j < 4; j++)
        {
            double d;
            if(j == 2 && i % 3 != 1) continue;
            d = sin(3.14159265358979323846 *(i + 0.5) / 36.0);
            if(j == 1)
            {
                if(i >= 30) d = 0;
                else if(i >= 24) d = sin(3.14159265358979323846 *((i - 18) + 0.5) / 12.0);
                else if(i >= 18) d = 1;
            }
            else if(j == 3)
            {
                if(i < 6) d = 0;
                else if(i < 12) d = sin(3.14159265358979323846 *((i - 6) + 0.5) / 12.0);
                else if(i < 18) d = 1;
            }
            d *= 0.5 / cos(3.14159265358979323846 *(2 * i + 19) / 72);
            if(j == 2) mdct_win[j][i / 3] =((int )(d /(1 << 5) *(1LL << 32) + 0.5));
            else mdct_win[j][i] =((int )(d /(1 << 5) *(1LL << 32) + 0.5));
        }
    }

#pragma endscop
}
