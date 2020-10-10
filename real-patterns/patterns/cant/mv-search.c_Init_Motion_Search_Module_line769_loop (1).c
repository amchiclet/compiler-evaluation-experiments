#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int byte_abs_range;
extern unsigned int * restrict byte_abs;

void loop()
{
#pragma scop

    for(i = 1; i < byte_abs_range / 2; i++) byte_abs[i] = byte_abs[-i] = i;

#pragma endscop
}
