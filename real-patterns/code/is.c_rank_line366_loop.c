#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
typedef int INT_TYPE;
extern INT_TYPE i;
extern INT_TYPE  key_buff1[1 << 23] ;

void loop()
{
#pragma scop

    for(i = 0; i < 1 << 19; i++) key_buff1[i] = 0;

#pragma endscop
}
