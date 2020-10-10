#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int ii;
extern int cCount;
extern unsigned char * restrict pArray;

void loop()
{
#pragma scop

    for(ii = 0; ii < cCount; ++ii)
    {
        pArray[ii] =(255 - pArray[ii]);
    }

#pragma endscop
}
