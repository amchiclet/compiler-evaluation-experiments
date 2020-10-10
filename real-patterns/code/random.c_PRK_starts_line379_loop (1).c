#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
typedef unsigned long long u64Int;
extern u64Int ran;
extern u64Int temp;
extern u64Int  m2[64] ;

void loop()
{
#pragma scop

    for(j = 0; j < 64; j++) if((unsigned int )(ran >> j & 1)) temp ^= m2[j];

#pragma endscop
}
