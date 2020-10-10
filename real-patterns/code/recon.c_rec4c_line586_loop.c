#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int h;
extern unsigned int s1;
extern unsigned char * restrict sp;
extern unsigned int s3;
extern unsigned char * restrict sp2;
extern unsigned char * restrict dp;
extern unsigned int s2;
extern unsigned int s4;
extern int lx2;
extern int lx;

void loop()
{
#pragma scop

    for(j = 0; j < h; j++)
    {
        s1 = sp[0];
        s3 = sp2[0];
        dp[0] =(((unsigned int )(s1 +(s2 = sp[1]) + s3 +(s4 = sp2[1]) + 2)) >> 2);
        dp[1] =(((unsigned int )(s2 +(s1 = sp[2]) + s4 +(s3 = sp2[2]) + 2)) >> 2);
        dp[2] =(((unsigned int )(s1 +(s2 = sp[3]) + s3 +(s4 = sp2[3]) + 2)) >> 2);
        dp[3] =(((unsigned int )(s2 +(s1 = sp[4]) + s4 +(s3 = sp2[4]) + 2)) >> 2);
        dp[4] =(((unsigned int )(s1 +(s2 = sp[5]) + s3 +(s4 = sp2[5]) + 2)) >> 2);
        dp[5] =(((unsigned int )(s2 +(s1 = sp[6]) + s4 +(s3 = sp2[6]) + 2)) >> 2);
        dp[6] =(((unsigned int )(s1 +(s2 = sp[7]) + s3 +(s4 = sp2[7]) + 2)) >> 2);
        dp[7] =(((unsigned int )(s2 + sp[8] + s4 + sp2[8] + 2)) >> 2);
        sp += lx2;
        sp2 += lx2;
        dp += lx;
    }

#pragma endscop
}
