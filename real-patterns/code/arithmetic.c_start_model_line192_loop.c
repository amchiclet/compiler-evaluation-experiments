#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int  freq[256 + 1 + 1] ;
extern int  cum_freq[256 + 1 + 1] ;

void loop()
{
#pragma scop

    for(i = 0; i <= 256 + 1; i++)
    {
        freq[i] = 1;
        cum_freq[i] = 256 + 1 - i;
    }

#pragma endscop
}
