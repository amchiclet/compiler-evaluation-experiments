#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int dst_width;
extern int sum;
extern uint8_t * restrict s;
extern int wrap;
typedef short int16_t;
extern int16_t * restrict filter;
typedef unsigned char uint8_t;
extern uint8_t * restrict dst;

void loop()
{
#pragma scop

    for(i = 0; i < dst_width; i++)
    {
        sum = s[0 * wrap] * filter[0] + s[1 * wrap] * filter[1] + s[2 * wrap] * filter[2] + s[3 * wrap] * filter[3];
        sum = sum >> 8;
        if(sum < 0) sum = 0;
        else if(sum > 255) sum = 255;
        dst[0] = sum;
        dst++;
        s++;
    }

#pragma endscop
}
