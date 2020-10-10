#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
typedef unsigned int uint32_t;
extern uint32_t  squareTbl[512] ;

void loop()
{
#pragma scop

    for(i = 0; i < 512; i++)
    {
        squareTbl[i] =((i - 256) *(i - 256));
    }

#pragma endscop
}
