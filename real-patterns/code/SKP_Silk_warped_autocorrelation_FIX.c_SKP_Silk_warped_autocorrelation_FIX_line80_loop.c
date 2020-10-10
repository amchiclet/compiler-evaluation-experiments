#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int order;
extern int * restrict corr;
typedef long int64_t;
extern int64_t  corr_QC[16 + 1] ;
extern int lsh;

void loop()
{
#pragma scop

    for(i = 0; i < order + 1; i++)
    {
        corr[i] =((int )(corr_QC[i] >> -lsh));
    }

#pragma endscop
}
