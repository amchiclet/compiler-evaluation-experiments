#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
typedef unsigned long uint64_t;
typedef uint64_t UInt8;
typedef UInt8 UInt;
extern UInt i;
extern UInt ll;
extern UInt elts;
typedef unsigned char uint8_t;
typedef uint8_t UInt1;
extern UInt1 bytel;
extern UInt1 * restrict ptrl;
extern UInt1 byte1;
extern UInt1 * restrict pmulltab;
extern UInt1 partr;
extern UInt p;
extern UInt1 * restrict ptrp;
extern UInt lr;
extern UInt1 * restrict addtab;
extern UInt1 * restrict pmulutab;

void loop()
{
#pragma scop

    for(i = 0; i < ll / elts; i++)
    {
        bytel = ptrl[i];
        if(bytel != 0)
        {
            byte1 = pmulltab[256 * partr + bytel];
            if(byte1 != 0)
            {
                if(p != 2) ptrp[lr / elts + i] = addtab[ptrp[lr / elts + i] + 256 * byte1];
                else ptrp[lr / elts + i] ^= byte1;
            }
            if(elts > 1)
            {
                byte1 = pmulutab[256 * partr + bytel];
                if(byte1 != 0)
                {
                    if(p != 2) ptrp[lr / elts + i + 1] = addtab[ptrp[lr / elts + i + 1] + 256 * byte1];
                    else ptrp[lr / elts + i + 1] ^= byte1;
                }
            }
        }
    }

#pragma endscop
}
