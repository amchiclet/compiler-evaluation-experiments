#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int j;
extern int32_t  is_table_lsf[2][2][16] ;

void loop()
{
#pragma scop

    for(i = 0; i < 16; i++)
    {
        double f;
        int e;
        int k;
        for(j = 0; j < 2; j++)
        {
            e = -(j + 1) *(i + 1 >> 1);
            f = pow(2.0,e / 4.0);
            k = i & 1;
            is_table_lsf[j][k ^ 1][i] =((int )(f *(1 << 23) + 0.5));
            is_table_lsf[j][k][i] =((int )(1.0 *(1 << 23) + 0.5));;
        }
    }

#pragma endscop
}
