#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
typedef long int64_t;
typedef int64_t Int8;
typedef Int8 Int;
extern Int i;
extern Int len;
typedef int int32_t;
typedef int32_t Int4;
extern Int4 hash;
typedef unsigned int uint32_t;
typedef uint32_t UInt4;
extern UInt4 * restrict ptr;
extern Int4 x;

void loop()
{
#pragma scop

    for(i = len; i >= 1; i--)
    {
        hash =((hash + *ptr %((Int4 )67108879L) * x) %((Int4 )67108879L));
        x =((8 * sizeof(UInt4 ) - 1) * x %((Int4 )67108879L));
        ptr++;
    }

#pragma endscop
}
