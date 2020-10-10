#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int height;
extern int i;
extern int width;
extern unsigned char * restrict ii;
extern unsigned char * restrict oo;

void loop()
{
#pragma scop

    for(j = 0; j < height - 1; j++)
    {
        for(i = 0; i < width - 1; i++)
        {
            *(ii +(i << 1)) = *(oo + i);
            *(ii +(i << 1) + 1) =(( *(oo + i)) +( *(oo + i + 1)) + 1 >> 1);
            *(ii +(i << 1) +(width << 1)) =(( *(oo + i)) +( *(oo + i + width)) + 1 >> 1);
            *(ii +(i << 1) + 1 +(width << 1)) =(( *(oo + i)) +( *(oo + i + 1)) +( *(oo + i + width)) +( *(oo + i + 1 + width)) + 2 >> 2);
        }*(ii +(width << 1) - 2) = *(oo + width - 1);
        *(ii +(width << 1) - 1) = *(oo + width - 1);
        *(ii +(width << 1) +(width << 1) - 2) =(( *(oo + width - 1)) +( *(oo + width + width - 1)) + 1 >> 1);
        *(ii +(width << 1) +(width << 1) - 1) =(( *(oo + width - 1)) +( *(oo + width + width - 1)) + 1 >> 1);
        ii += width << 2;
        oo += width;
    }

#pragma endscop
}
