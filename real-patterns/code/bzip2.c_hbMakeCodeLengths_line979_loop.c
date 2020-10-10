#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int alphaSize;
extern int  weight[258 * 2] ;
extern int * restrict freq;

void loop()
{
#pragma scop

    for(i = 0; i < alphaSize; i++) weight[i + 1] =((freq[i] == 0?1 : freq[i])) << 8;

#pragma endscop
}
