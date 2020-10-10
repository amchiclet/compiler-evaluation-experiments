#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int last;
extern unsigned short * restrict quadrant;

void loop()
{
#pragma scop

    for(i = 0; i <= last + 20; i++) quadrant[i] = 0;

#pragma endscop
}
