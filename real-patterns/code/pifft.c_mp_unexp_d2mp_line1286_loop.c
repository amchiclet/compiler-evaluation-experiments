#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int n;
extern int x;
extern double din;
extern int radix;
extern int* restrict out;

void loop()
{
#pragma scop

    for(j = 0; j < n; j++)
    {
        x =((int )din);
        if(x >= radix)
        {
            x = radix - 1;
            din = radix;
        }
        din = radix *(din - x);
        out[j] = x;
    }

#pragma endscop
}
