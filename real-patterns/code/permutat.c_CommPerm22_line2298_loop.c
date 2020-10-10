#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
typedef unsigned long uint64_t;
typedef uint64_t UInt8;
typedef UInt8 UInt;
extern UInt p;
extern UInt degC;
typedef unsigned short uint16_t;
typedef uint16_t UInt2;
extern UInt2 * restrict ptC;
extern UInt degR;
extern UInt2 * restrict ptR;
extern UInt degL;
extern UInt2 * restrict ptL;

void loop()
{
#pragma scop

    for(p = 0; p < degC; p++) ptC[(((p < degR?ptR[p] : p)) < degL?ptL[(p < degR?ptR[p] : p)] :((p < degR?ptR[p] : p)))] =((((p < degL?ptL[p] : p)) < degR?ptR[(p < degL?ptL[p] : p)] :((p < degL?ptL[p] : p))));

#pragma endscop
}
