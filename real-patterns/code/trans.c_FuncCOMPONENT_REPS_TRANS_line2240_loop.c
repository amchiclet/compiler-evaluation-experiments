#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
typedef unsigned long uint64_t;
typedef uint64_t UInt8;
typedef UInt8 UInt;
extern UInt i;
extern UInt deg;
typedef unsigned int uint32_t;
typedef uint32_t UInt4;
extern UInt4 * restrict ptimg;
typedef unsigned short uint16_t;
typedef uint16_t UInt2;
extern UInt2 * restrict ptf2;

void loop()
{
#pragma scop

    for(i = 0; i < deg; i++) ptimg[ptf2[i]] = 1;

#pragma endscop
}
