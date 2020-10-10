#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
typedef unsigned long uint64_t;
typedef uint64_t UInt8;
typedef UInt8 UInt;
extern UInt j;
extern UInt deg;
typedef unsigned short uint16_t;
typedef uint16_t UInt2;
extern UInt2 * restrict ptf2;
extern UInt i;
typedef UInt ** Bag;
typedef long int64_t;
typedef int64_t Int8;
typedef Int8 Int;
extern Bag restrict out;
extern UInt nr;

void loop()
{
#pragma scop

    for(j = 0; j < deg; j++) if(ptf2[j] == i) do
            {
                Bag sep_Obj =(Bag )((((Int )(j + 1)) << 2) + 0x01);
                ( *((Bag **)out))[++nr] = sep_Obj;
            }
            while(0);

#pragma endscop
}
