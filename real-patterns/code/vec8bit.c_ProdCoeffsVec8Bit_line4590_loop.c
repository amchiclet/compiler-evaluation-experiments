#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
typedef unsigned long uint64_t;
typedef uint64_t UInt8;
typedef UInt8 UInt;
extern UInt j;
extern UInt lr;
extern UInt elts;
typedef unsigned char uint8_t;
typedef uint8_t UInt1;
extern UInt1 byter;
extern UInt1 * restrict ptrr;
extern UInt1 byte2;
extern UInt1 * restrict pmulltab;
extern UInt1 partl;
extern UInt p;
extern UInt1 * restrict ptrp;
extern UInt ll;
extern UInt1 * restrict addtab;
extern UInt1 * restrict pmulutab;

void loop()
{
#pragma scop

    for(j = 0; j < lr / elts; j++)
    {
        byter = ptrr[j];
        if(byter != 0)
        {
            byte2 = pmulltab[256 * partl + byter];
            if(byte2 != 0)
            {
                if(p != 2) ptrp[ll / elts + j] = addtab[ptrp[ll / elts + j] + 256 * byte2];
                else ptrp[ll / elts + j] ^= byte2;
            }
            if(elts > 1)
            {
                byte2 = pmulutab[256 * partl + byter];
                if(byte2 != 0)
                {
                    if(p != 2) ptrp[ll / elts + j + 1] = addtab[ptrp[ll / elts + j + 1] + 256 * byte2];
                    else ptrp[ll / elts + j + 1] ^= byte2;
                }
            }
        }
    }

#pragma endscop
}
