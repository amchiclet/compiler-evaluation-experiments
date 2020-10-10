#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int  freq[256 + 1 + 1] ;
extern int  cum_freq[256 + 1 + 1] ;
extern int cum;

void loop()
{
#pragma scop

    for(i = 256 + 1; i >= 0; i--)
    {
        freq[i] =(freq[i] + 1) / 2;
        cum_freq[i] = cum;
        cum += freq[i];
    }

#pragma endscop
}
