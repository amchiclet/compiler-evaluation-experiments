#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern unsigned char * restrict rfp;
extern unsigned char * restrict clp;
extern short * restrict bp;
extern int iincr;

void loop()
{
#pragma scop

    for(i = 0; i < 8; i++)
    {
        rfp[0] = clp[bp[0] + rfp[0]];
        rfp[1] = clp[bp[1] + rfp[1]];
        rfp[2] = clp[bp[2] + rfp[2]];
        rfp[3] = clp[bp[3] + rfp[3]];
        rfp[4] = clp[bp[4] + rfp[4]];
        rfp[5] = clp[bp[5] + rfp[5]];
        rfp[6] = clp[bp[6] + rfp[6]];
        rfp[7] = clp[bp[7] + rfp[7]];
        bp += 8;
        rfp += iincr;
    }

#pragma endscop
}
