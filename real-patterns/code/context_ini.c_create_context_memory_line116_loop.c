#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
extern double  probability[128] ;
extern double  entropy[128] ;

void loop()
{
#pragma scop

    for(k = 0; k < 64; k++)
    {
        probability[k] = 1.0 - probability[127 - k];
        entropy[k] = log10(probability[k]) / log10(2.0);
        entropy[127 - k] = log10(probability[127 - k]) / log10(2.0);
    }

#pragma endscop
}
