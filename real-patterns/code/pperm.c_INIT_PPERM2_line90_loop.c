#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
typedef unsigned long uint64_t;
typedef uint64_t UInt8;
typedef UInt8 UInt;
extern UInt i;
extern UInt deg;
typedef unsigned short uint16_t;
typedef uint16_t UInt2;
extern UInt2 * restrict ptf;
extern UInt rank;
typedef UInt ** Bag;
typedef long int64_t;
typedef int64_t Int8;
typedef Int8 Int;
extern Bag restrict dom;
extern Bag restrict img;

void loop()
{
#pragma scop

    for(i = 0; i < deg; i++)
    {
        if(ptf[i] != 0)
        {
            rank++;
            do
            {
                Bag sep_Obj =(Bag )((((Int )(i + 1)) << 2) + 0x01);
                ( *((Bag **)dom))[rank] = sep_Obj;
            }
            while(0);
            do
            {
                Bag sep_Obj =(Bag )((((Int )ptf[i]) << 2) + 0x01);
                ( *((Bag **)img))[rank] = sep_Obj;
            }
            while(0);
        }
    }

#pragma endscop
}
