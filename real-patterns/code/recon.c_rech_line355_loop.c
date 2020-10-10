#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int h;
extern unsigned int s1;
extern unsigned char * restrict sp;
extern unsigned char * restrict dp;
extern unsigned int s2;
extern int lx2;
extern int lx;

void loop()
{
#pragma scop

    for(j = 0; j < h; j++)
    {
        s1 = sp[0];
        dp[0] =(((unsigned int )(s1 +(s2 = sp[1]) + 1)) >> 1);
        dp[1] =(((unsigned int )(s2 +(s1 = sp[2]) + 1)) >> 1);
        dp[2] =(((unsigned int )(s1 +(s2 = sp[3]) + 1)) >> 1);
        dp[3] =(((unsigned int )(s2 +(s1 = sp[4]) + 1)) >> 1);
        dp[4] =(((unsigned int )(s1 +(s2 = sp[5]) + 1)) >> 1);
        dp[5] =(((unsigned int )(s2 +(s1 = sp[6]) + 1)) >> 1);
        dp[6] =(((unsigned int )(s1 +(s2 = sp[7]) + 1)) >> 1);
        dp[7] =(((unsigned int )(s2 +(s1 = sp[8]) + 1)) >> 1);
        dp[8] =(((unsigned int )(s1 +(s2 = sp[9]) + 1)) >> 1);
        dp[9] =(((unsigned int )(s2 +(s1 = sp[10]) + 1)) >> 1);
        dp[10] =(((unsigned int )(s1 +(s2 = sp[11]) + 1)) >> 1);
        dp[11] =(((unsigned int )(s2 +(s1 = sp[12]) + 1)) >> 1);
        dp[12] =(((unsigned int )(s1 +(s2 = sp[13]) + 1)) >> 1);
        dp[13] =(((unsigned int )(s2 +(s1 = sp[14]) + 1)) >> 1);
        dp[14] =(((unsigned int )(s1 +(s2 = sp[15]) + 1)) >> 1);
        dp[15] =(((unsigned int )(s2 + sp[16] + 1)) >> 1);
        sp += lx2;
        dp += lx;
    }

#pragma endscop
}
