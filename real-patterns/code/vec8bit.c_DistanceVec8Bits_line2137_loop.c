#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
typedef unsigned long uint64_t;
typedef uint64_t UInt8;
typedef UInt8 UInt;
extern UInt i;
extern UInt elts;
typedef unsigned char uint8_t;
typedef uint8_t UInt1;
extern UInt1 * restrict gettab;
extern UInt1 * restrict ptrL;
extern UInt1 * restrict ptrR;
extern UInt acc;

void loop()
{
#pragma scop

    for(i = 0; i < elts; i++) if(gettab[( *ptrL) + 256 * i] != gettab[( *ptrR) + 256 * i]) acc++;

#pragma endscop
}
