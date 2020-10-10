#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
typedef int INT_TYPE;
extern INT_TYPE i;
extern INT_TYPE  key_buff1[1 << 23] ;

void loop()
{
#pragma scop

    for(i = 0; i <(1 << 19) - 1; i++) key_buff1[i + 1] += key_buff1[i];

#pragma endscop
}
