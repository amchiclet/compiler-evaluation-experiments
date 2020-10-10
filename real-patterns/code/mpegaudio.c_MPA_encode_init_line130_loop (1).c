#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int32_t  mpa_enwindow[257] ;
typedef short int16_t;
extern int16_t  filter_bank[512] ;

void loop()
{
#pragma scop

    for(i = 0; i < 257; i++)
    {
        int v;
        v = mpa_enwindow[i];
        v = v +(1 << 16 - 14 - 1) >> 16 - 14;
        filter_bank[i] = v;
        if((i & 63) != 0) v = -v;
        if(i != 0) filter_bank[512 - i] = v;
    }

#pragma endscop
}
