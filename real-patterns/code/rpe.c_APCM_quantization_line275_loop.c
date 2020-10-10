#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
typedef short word;
extern word temp;
extern word * restrict xM;
extern word xmax;

void loop()
{
#pragma scop

    for(i = 0; i <= 12; i++)
    {
        temp = xM[i];
        temp =((temp < 0?((temp == - 32767 - 1?32767 : -temp)) : temp));
        if(temp > xmax) xmax = temp;
    }

#pragma endscop
}
