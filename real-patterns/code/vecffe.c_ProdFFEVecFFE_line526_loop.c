#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
typedef unsigned long uint64_t;
typedef uint64_t UInt8;
typedef UInt8 UInt;
extern UInt i;
extern UInt len;
typedef unsigned short uint16_t;
typedef uint16_t UInt2;
typedef UInt2 FFV;
extern FFV valR;
typedef UInt ** Bag;
extern Bag * restrict ptrR;
extern FFV valP;
extern FFV valL;
typedef UInt2 FF;
extern FF * restrict succ;
extern Bag * restrict ptrP;
extern FF fld;

void loop()
{
#pragma scop

    for(i = 1; i <= len; i++)
    {
        valR =((FFV )(((UInt )ptrR[i]) >> 16));
        valP =((valL == 0 || valR == 0?0 :((valL - 1 <=( *succ) - valR?valL - 1 + valR : valL - 1 -(( *succ) - valR)))));
        ptrP[i] =((Bag )((((UInt )valP) << 16) +(((UInt )fld) << 3) +((UInt )0x02)));
    }

#pragma endscop
}
