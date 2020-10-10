#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int bin;
extern int start;
extern int end;
typedef short int16_t;
extern int16_t  psd[256] ;
typedef signed char int8_t;
extern int8_t * restrict exp;

void loop()
{
#pragma scop

    for(bin = start; bin < end; bin++)
    {
        psd[bin] =(3072 -(exp[bin] << 7));
    }

#pragma endscop
}
