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
extern FFV val;
typedef UInt ** Bag;
extern Bag * restrict ptr;
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
        val =((FFV )(((UInt )ptr[i]) >> 16));
        valS =((val == 0 || valM == 0?0 :((val - 1 <=( *succ) - valM?val - 1 + valM : val - 1 -(( *succ) - valM)))));
        ptr[i] =((Bag )((((UInt )valS) << 16) +(((UInt )fld) << 3) +((UInt )0x02)));
    }

#pragma endscop
}
