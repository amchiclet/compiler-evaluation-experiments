#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
typedef short word;
extern word temp;
extern word * restrict s;
extern word smax;

void loop()
{
#pragma scop

    for(k = 0; k <= 159; k++)
    {
        temp =((s[k] < 0?((s[k] == - 32767 - 1?32767 : -s[k])) : s[k]));
        if(temp > smax) smax = temp;
    }

#pragma endscop
}
