#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
extern int len;
extern int sum;
extern int * restrict pulses_in;
extern int max_pulses;
extern int * restrict pulses_comb;

void loop()
{
#pragma scop

    for(k = 0; k < len; k++)
    {
        sum = pulses_in[2 * k] + pulses_in[2 * k + 1];
        if(sum > max_pulses)
        {
            return 1;
        }
        pulses_comb[k] = sum;
    }

#pragma endscop
}
