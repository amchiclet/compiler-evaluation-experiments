#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
typedef short word;
extern word temp;
extern word * restrict d;
extern word dmax;

void loop()
{
#pragma scop

    for(k = 0; k <= 39; k++)
    {
        temp = d[k];
        temp =((temp < 0?((temp == - 32767 - 1?32767 : -temp)) : temp));
        if(temp > dmax) dmax = temp;
    }

#pragma endscop
}
