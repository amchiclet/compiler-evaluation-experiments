#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int len;
extern int sum;
extern short * restrict inVec1;
extern short * restrict inVec2;

void loop()
{
#pragma scop

    for(i = 0; i < len; i++)
    {
        sum = sum +((int )((short )inVec1[i])) *((int )((short )inVec2[i]));
    }

#pragma endscop
}
