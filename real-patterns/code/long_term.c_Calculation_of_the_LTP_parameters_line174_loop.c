#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
typedef long longword;
typedef short word;
extern word * restrict dp;
extern word Nc;
extern longword L_power;

void loop()
{
#pragma scop

    for(k = 0; k <= 39; k++)
    {
        register longword L_temp;
        L_temp =(dp[k - Nc] >> 3);
        L_power += L_temp * L_temp;
    }

#pragma endscop
}
