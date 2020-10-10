#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
typedef int INT_TYPE;
extern INT_TYPE i;
extern INT_TYPE  key_array[1 << 23] ;
extern INT_TYPE j;

void loop()
{
#pragma scop

    for(i = 1; i < 1 << 23; i++) if(key_array[i - 1] > key_array[i]) j++;

#pragma endscop
}
