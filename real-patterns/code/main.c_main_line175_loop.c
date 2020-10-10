#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern double * restrict desired_accept;

void loop()
{
#pragma scop

    for(i = 0; i <= 116; i++)
    {
        if(i < 7)
        {
            desired_accept[i] = 50.0;
        }
        else
        {
            desired_accept[i] = 50.5 - 50.0 / 110.0 *((double )(i - 6));
        }
    }

#pragma endscop
}
