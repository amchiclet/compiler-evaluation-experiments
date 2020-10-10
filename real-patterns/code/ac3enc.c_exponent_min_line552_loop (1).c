#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
typedef unsigned char uint8_t;
extern uint8_t  exp1[(1 << 9) / 2] ;
extern uint8_t  exp[(1 << 9) / 2] ;

void loop()
{
#pragma scop

    for(i = 0; i < n; i++)
    {
        if(exp1[i] < exp[i]) exp[i] = exp1[i];
    }

#pragma endscop
}
