#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int n;
extern int k;
extern int tmp_QA;
extern int * restrict Aold_QA;
typedef long int64_t;
extern int rc_Q31;
extern int * restrict Anew_QA;
extern int rc_mult2_Q16;
extern int headrm;

void loop()
{
#pragma scop

    for(n = 0; n < k; n++)
    {
        tmp_QA = Aold_QA[n] -(((int )(((int64_t )Aold_QA[k - n - 1]) * rc_Q31 >> 32)) << 1);
        Anew_QA[n] =((int )(((int64_t )tmp_QA) * rc_mult2_Q16 >> 32)) << 16 - headrm;
    }

#pragma endscop
}
