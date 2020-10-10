#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int len;
extern int lvl;
extern short * restrict vec;
extern int max;
extern int ind;

void loop()
{
#pragma scop

    for(i = len - 2; i >= 0; i--)
    {
        lvl =((int )((short )vec[i])) *((int )((short )vec[i]));
        if(lvl > max)
        {
            max = lvl;
            ind = i;
        }
    }

#pragma endscop
}
