#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
typedef unsigned long size_t;
extern size_t i;
extern size_t len;
typedef unsigned int uint32_t;
extern uint32_t elems;
extern uint32_t * restrict Array;

void loop()
{
#pragma scop

    for(i = 0; i < len; i++) elems += Array[i];

#pragma endscop
}
