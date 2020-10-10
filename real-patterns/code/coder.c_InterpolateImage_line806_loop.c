#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int width;
extern unsigned char * restrict ii;
extern unsigned char * restrict oo;

void loop()
{
#pragma scop

    for(i = 0; i < width - 1; i++)
    {
        *(ii +(i << 1)) = *(oo + i);
        *(ii +(i << 1) + 1) =(( *(oo + i)) +( *(oo + i + 1)) + 1 >> 1);
        *(ii +(width << 1) +(i << 1)) = *(oo + i);
        *(ii +(width << 1) +(i << 1) + 1) =(( *(oo + i)) +( *(oo + i + 1)) + 1 >> 1);
    }

#pragma endscop
}
