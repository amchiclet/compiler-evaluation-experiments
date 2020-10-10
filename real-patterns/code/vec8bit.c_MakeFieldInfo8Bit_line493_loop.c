#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
typedef unsigned long uint64_t;
typedef uint64_t UInt8;
typedef UInt8 UInt;
extern UInt i;
extern UInt e;
extern UInt j;
typedef unsigned char uint8_t;
typedef uint8_t UInt1;
extern UInt1 * restrict getelt_info;
extern UInt  pows[7] ;
extern UInt q;

void loop()
{
#pragma scop

    for(i = 0; i < e; i++) for(j = 0; j < 256; j++) getelt_info[i * 256 + j] =(((UInt1 )(j / pows[i])) % q);

#pragma endscop
}
