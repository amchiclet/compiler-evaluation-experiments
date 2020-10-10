#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
typedef unsigned long uint64_t;
typedef uint64_t UInt8;
typedef UInt8 UInt;
extern UInt i;
extern UInt lr;
extern UInt elts;
typedef unsigned char uint8_t;
typedef uint8_t UInt1;
extern UInt1 partr;
extern UInt1 * restrict settab;
extern UInt1 * restrict gettab;
extern UInt1 byter;

void loop()
{
#pragma scop

    for(i = lr / elts * elts; i < lr; i++) partr = settab[partr + 256 *(i % elts + elts * gettab[byter + 256 *(i % elts)])];

#pragma endscop
}
