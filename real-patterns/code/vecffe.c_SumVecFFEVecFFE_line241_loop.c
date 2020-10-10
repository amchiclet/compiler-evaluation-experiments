#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
typedef unsigned long uint64_t;
typedef uint64_t UInt8;
typedef UInt8 UInt;
extern UInt i;
extern UInt lenmin;
typedef unsigned short uint16_t;
typedef uint16_t UInt2;
typedef UInt2 FFV;
extern FFV valL;
typedef UInt ** Bag;
extern Bag * restrict ptrL;
extern FFV valR;
extern Bag * restrict ptrR;
extern FFV valS;
typedef UInt2 FF;
extern FF * restrict succ;
extern Bag * restrict ptrS;
extern FF fld;

void loop()
{
#pragma scop

    for(i = 1; i <= lenmin; i++)
    {
        valL =((FFV )(((UInt )ptrL[i]) >> 16));
        valR =((FFV )(((UInt )ptrR[i]) >> 16));
        valS =((valL == 0 || valR == 0?valL + valR :((valL <= valR?((valL == 0 || succ[valR - valL + 1] == 0?0 :((valL - 1 <=( *succ) - succ[valR - valL + 1]?valL - 1 + succ[valR - valL + 1] : valL - 1 -(( *succ) - succ[valR - valL + 1]))))) :((valR == 0 || succ[valL - valR + 1] == 0?0 :((valR - 1 <=( *succ) - succ[valL - valR + 1]?valR - 1 + succ[valL - valR + 1] : valR - 1 -(( *succ) - succ[valL - valR + 1])))))))));
        ptrS[i] =((Bag )((((UInt )valS) << 16) +(((UInt )fld) << 3) +((UInt )0x02)));
    }

#pragma endscop
}
