#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
typedef char base;
extern base  seq[2500 + 0] ;

void loop()
{
#pragma scop

    for(i = 0; i < n; i++)
    {
        seq[i] =((base )((i + 1) % 4));
    }

#pragma endscop
}
