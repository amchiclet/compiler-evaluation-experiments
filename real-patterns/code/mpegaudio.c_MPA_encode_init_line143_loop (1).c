#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int v;
extern int  scale_factor_table[64] ;
typedef signed char int8_t;
extern int8_t  scale_factor_shift[64] ;
extern unsigned short  scale_factor_mult[64] ;

void loop()
{
#pragma scop

    for(i = 0; i < 64; i++)
    {
        v =((int )(pow(2.0,(3 - i) / 3.0) *(1 << 20)));
        if(v <= 0) v = 1;
        scale_factor_table[i] = v;
        scale_factor_shift[i] =(21 - 15 - i / 3);
        scale_factor_mult[i] =((1 << 15) * pow(2.0,(i % 3) / 3.0));
    }

#pragma endscop
}
