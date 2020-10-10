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
extern FFV valP;
typedef UInt2 FF;
extern FF * restrict succ;
extern FFV valS;

void loop()
{
#pragma scop

    for(i = 1; i <= len; i++)
    {
        valL =((FFV )(((UInt )ptrL[i]) >> 16));
        valR =((FFV )(((UInt )ptrR[i]) >> 16));
        valP =((valL == 0 || valR == 0?0 :((valL - 1 <=( *succ) - valR?valL - 1 + valR : valL - 1 -(( *succ) - valR)))));
        valS =((valS == 0 || valP == 0?valS + valP :((valS <= valP?((valS == 0 || succ[valP - valS + 1] == 0?0 :((valS - 1 <=( *succ) - succ[valP - valS + 1]?valS - 1 + succ[valP - valS + 1] : valS - 1 -(( *succ) - succ[valP - valS + 1]))))) :((valP == 0 || succ[valS - valP + 1] == 0?0 :((valP - 1 <=( *succ) - succ[valS - valP + 1]?valP - 1 + succ[valS - valP + 1] : valP - 1 -(( *succ) - succ[valS - valP + 1])))))))));
    }

#pragma endscop
}
