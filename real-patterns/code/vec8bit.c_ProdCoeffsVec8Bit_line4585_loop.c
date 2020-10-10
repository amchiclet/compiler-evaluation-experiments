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
extern UInt1 byte1;
extern UInt1 * restrict gettab;
extern UInt1 bytel;
extern UInt1 partl;
extern UInt1 * restrict settab;

void loop()
{
#pragma scop

    for(i = ll / elts * elts; i < ll; i++)
    {
        byte1 = gettab[bytel + 256 *(i % elts)];
        partl = settab[partl + 256 *(i % elts + elts * byte1)];
    }

#pragma endscop
}
