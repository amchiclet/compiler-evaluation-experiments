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
extern FFV valL;
typedef UInt ** Bag;
extern Bag * restrict ptrL;
extern FFV valR;
extern Bag * restrict ptrR;
extern FFV valS;
extern FFV valM;
extern FFV * restrict succ;
typedef UInt2 FF;
extern FF fld;

void loop()
{
#pragma scop

    for(i = 1; i <= len; i++)
    {
        valL =((FFV )(((UInt )ptrL[i]) >> 16));
        valR =((FFV )(((UInt )ptrR[i]) >> 16));
        valS =((valR == 0 || valM == 0?0 :((valR - 1 <=( *succ) - valM?valR - 1 + valM : valR - 1 -(( *succ) - valM)))));
        valS =((valL == 0 || valS == 0?valL + valS :((valL <= valS?((valL == 0 || succ[valS - valL + 1] == 0?0 :((valL - 1 <=( *succ) - succ[valS - valL + 1]?valL - 1 + succ[valS - valL + 1] : valL - 1 -(( *succ) - succ[valS - valL + 1]))))) :((valS == 0 || succ[valL - valS + 1] == 0?0 :((valS - 1 <=( *succ) - succ[valL - valS + 1]?valS - 1 + succ[valL - valS + 1] : valS - 1 -(( *succ) - succ[valL - valS + 1])))))))));
        ptrL[i] =((Bag )((((UInt )valS) << 16) +(((UInt )fld) << 3) +((UInt )0x02)));
    }

#pragma endscop
}
