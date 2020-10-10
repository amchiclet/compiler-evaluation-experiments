#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
typedef long int64_t;
typedef int64_t Int8;
typedef Int8 Int;
extern Int j;
typedef unsigned long uint64_t;
typedef uint64_t UInt8;
typedef UInt8 UInt;
extern UInt lrs;
extern UInt elts;
typedef unsigned char uint8_t;
typedef uint8_t UInt1;
extern UInt1 y;
extern UInt1 * restrict multab;
extern UInt1 * restrict ptrr;
extern UInt p;
extern UInt1 * restrict ptrl1;
extern UInt1 * restrict addtab;

void loop()
{
#pragma scop

    for(j =((lrs - 1) / elts); j >= 0; j--)
    {
        y = multab[ *ptrr];
        if(p == 2) *ptrl1 ^= y;
        else *ptrl1 = addtab[( *ptrl1) + 256 * y];
        ptrl1--;
        ptrr--;
    }

#pragma endscop
}
