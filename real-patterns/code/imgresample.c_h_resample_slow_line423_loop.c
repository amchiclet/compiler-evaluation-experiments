#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern uint8_t * restrict s;
extern uint8_t * restrict src;
extern int v;
extern uint8_t * restrict src_end;
extern int sum;
typedef short int16_t;
extern int16_t * restrict filter;

void loop()
{
#pragma scop

    for(j = 0; j < 4; j++)
    {
        if(s < src) v = src[0];
        else if(s >= src_end) v = src_end[- 1];
        else v = s[0];
        sum += v * filter[j];
        s++;
    }

#pragma endscop
}
