#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
typedef unsigned long long u64Int;
extern u64Int  m2[64] ;
extern u64Int temp;
typedef long long s64Int;

void loop()
{
#pragma scop

    for(i = 0; i < 64; i++)
    {
        m2[i] = temp;
        temp = temp << 1 ^((((s64Int )temp) < 0?0x0000000000000007ULL : 0));
        temp = temp << 1 ^((((s64Int )temp) < 0?0x0000000000000007ULL : 0));
    }

#pragma endscop
}
