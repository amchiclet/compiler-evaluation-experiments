#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int n;
extern int order;
extern int k;
extern int Ctmp1_Q30;
extern int  C[16 + 1][2] ;
extern int Ctmp2_Q30;
typedef long int64_t;
extern int rc_tmp_Q31;

void loop()
{
#pragma scop

    for(n = 0; n < order - k; n++)
    {
        Ctmp1_Q30 = C[n + k + 1][0];
        Ctmp2_Q30 = C[n][1];
        C[n + k + 1][0] = Ctmp1_Q30 +((int )(((int64_t )(Ctmp2_Q30 << 1)) * rc_tmp_Q31 >> 32));
        C[n][1] = Ctmp2_Q30 +((int )(((int64_t )(Ctmp1_Q30 << 1)) * rc_tmp_Q31 >> 32));
    }

#pragma endscop
}
