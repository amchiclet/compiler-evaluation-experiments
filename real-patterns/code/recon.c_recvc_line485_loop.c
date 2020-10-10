#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int h;
extern unsigned char * restrict dp;
extern unsigned char * restrict sp;
extern unsigned char * restrict sp2;
extern int lx2;
extern int lx;

void loop()
{
#pragma scop

    for(j = 0; j < h; j++)
    {
        dp[0] =(((unsigned int )(sp[0] + sp2[0] + 1)) >> 1);
        dp[1] =(((unsigned int )(sp[1] + sp2[1] + 1)) >> 1);
        dp[2] =(((unsigned int )(sp[2] + sp2[2] + 1)) >> 1);
        dp[3] =(((unsigned int )(sp[3] + sp2[3] + 1)) >> 1);
        dp[4] =(((unsigned int )(sp[4] + sp2[4] + 1)) >> 1);
        dp[5] =(((unsigned int )(sp[5] + sp2[5] + 1)) >> 1);
        dp[6] =(((unsigned int )(sp[6] + sp2[6] + 1)) >> 1);
        dp[7] =(((unsigned int )(sp[7] + sp2[7] + 1)) >> 1);
        sp += lx2;
        sp2 += lx2;
        dp += lx;
    }

#pragma endscop
}
