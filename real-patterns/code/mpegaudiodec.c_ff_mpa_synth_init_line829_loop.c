#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int32_t  mpa_enwindow[257] ;
typedef int int32_t;
typedef int32_t MPA_INT;
extern MPA_INT * restrict window;

void loop()
{
#pragma scop

    for(i = 0; i < 257; i++)
    {
        int v;
        v = mpa_enwindow[i];
        window[i] = v;
        if((i & 63) != 0) v = -v;
        if(i != 0) window[512 - i] = v;
    }

#pragma endscop
}
