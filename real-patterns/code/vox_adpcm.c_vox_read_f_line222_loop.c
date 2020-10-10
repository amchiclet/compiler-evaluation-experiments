#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
extern int readcount;
extern float * restrict ptr;
typedef long int64_t;
typedef int64_t sf_count_t;
extern sf_count_t total;
extern float normfact;
extern short * restrict sptr;

void loop()
{
#pragma scop

    for(k = 0; k < readcount; k++) ptr[total + k] = normfact *((float )sptr[k]);

#pragma endscop
}
