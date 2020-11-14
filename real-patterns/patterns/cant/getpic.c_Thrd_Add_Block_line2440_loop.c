#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int j;
extern short tmp;
extern short * restrict bptr;
extern unsigned char * restrict rfp;
extern int iincr;

void loop()
{
#pragma scop

    for(i = 0; i < 4; i++)
    {
        for(j = 0; j < 8; j++)
        {
            tmp =(( *bptr) +( *rfp));
            tmp =((tmp < 0?0 :((tmp > 255?255 : tmp))));
            *rfp = tmp;
            bptr++;
            rfp++;
        }
        rfp += iincr;
        for(j = 0; j < 8; j++)
        {
            tmp =(( *bptr) +( *rfp));
            tmp =((tmp < 0?0 :((tmp > 255?255 : tmp))));
            *rfp = tmp;
            bptr++;
            rfp++;
        }
        rfp += iincr;
    }

#pragma endscop
}
