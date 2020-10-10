#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int  history_w[4096] ;
extern int  history_b[4096] ;

void loop()
{
#pragma scop

    for(i = 0; i < 4096; i++)
    {
        history_w[i] = history_w[i] >> 8;
        history_b[i] = history_b[i] >> 8;
    }

#pragma endscop
}
