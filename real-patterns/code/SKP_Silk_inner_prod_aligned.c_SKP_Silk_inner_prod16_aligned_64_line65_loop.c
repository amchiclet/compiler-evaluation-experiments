#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int len;
typedef long int64_t;
extern int64_t sum;
extern short * restrict inVec1;
extern short * restrict inVec2;

void loop()
{
#pragma scop

    for(i = 0; i < len; i++)
    {
        sum = sum +((int64_t )(((int )inVec1[i]) *((int )inVec2[i])));
    }

#pragma endscop
}
