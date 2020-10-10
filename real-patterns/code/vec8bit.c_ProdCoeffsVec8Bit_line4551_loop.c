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
extern UInt j;
extern UInt lr;
extern UInt1 byter;
extern UInt1 * restrict ptrr;
extern UInt1 byte1;
extern UInt1 * restrict pmulltab;
extern UInt p;
extern UInt1 * restrict ptrp;
extern UInt1 * restrict addtab;
extern UInt1 byte2;
extern UInt1 * restrict pmulutab;

void loop()
{
#pragma scop

    for(i = 0; i < ll / elts; i++)
    {
        bytel = ptrl[i];
        if(bytel != 0) for(j = 0; j < lr / elts; j++)
            {
                byter = ptrr[j];
                if(byter != 0)
                {
                    byte1 = pmulltab[256 * bytel + byter];
                    if(byte1 != 0)
                    {
                        if(p != 2) ptrp[i + j] = addtab[ptrp[i + j] + 256 * byte1];
                        else ptrp[i + j] ^= byte1;
                    }
                    if(elts > 1)
                    {
                        byte2 = pmulutab[256 * bytel + byter];
                        if(byte2 != 0)
                        {
                            if(p != 2) ptrp[i + j + 1] = addtab[ptrp[i + j + 1] + 256 * byte2];
                            else ptrp[i + j + 1] ^= byte2;
                        }
                    }
                }
            }
    }

#pragma endscop
}
