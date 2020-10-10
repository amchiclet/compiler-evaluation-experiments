#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
typedef unsigned long uint64_t;
typedef uint64_t UInt8;
typedef UInt8 UInt;
extern UInt i;
extern UInt deg;
extern UInt j;
extern UInt degf;
typedef unsigned short uint16_t;
typedef uint16_t UInt2;
extern UInt2 * restrict ptf2;
extern UInt degg;
extern UInt2 * restrict ptg2;
extern UInt2 * restrict ptmeet2;
extern UInt codeg;

void loop()
{
#pragma scop

    for(i = 0; i < deg; i++)
    {
        j =((i + 1 <= degf?ptf2[i + 1 - 1] : 0));
        if(((i + 1 <= degg?ptg2[i + 1 - 1] : 0)) == j)
        {
            ptmeet2[i] = j;
            if(j > codeg) codeg = j;
        }
    }

#pragma endscop
}
