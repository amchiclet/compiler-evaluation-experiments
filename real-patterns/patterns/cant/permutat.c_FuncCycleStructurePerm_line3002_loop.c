#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
typedef unsigned long uint64_t;
typedef uint64_t UInt8;
typedef UInt8 UInt;
extern UInt cnt;
extern UInt ende;
extern UInt pnt;
typedef unsigned short uint16_t;
typedef uint16_t UInt2;
extern UInt2 * restrict offset2;
typedef UInt ** Bag;
extern Bag * restrict ptList;

void loop()
{
#pragma scop

    for(cnt = 0; cnt < ende; cnt++)
    {
        pnt =((UInt )offset2[cnt]);
        pnt--;
        ptList[pnt] =((Bag )(((UInt )ptList[pnt]) + 1));
    }

#pragma endscop
}
