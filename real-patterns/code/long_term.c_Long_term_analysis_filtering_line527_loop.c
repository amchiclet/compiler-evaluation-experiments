#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
typedef short word;
extern word * restrict dpp;
typedef long longword;
extern word * restrict dp;
extern word Nc;
extern word * restrict e;
extern longword ltmp;
extern word * restrict d;

void loop()
{
#pragma scop

    for(k = 0; k <= 39; k++)
    {
        dpp[k] =(((longword )21299) *((longword )dp[k - Nc]) + 16384 >> 15);
        e[k] =(((ltmp =((longword )d[k]) -((longword )dpp[k])) >= 32767?32767 :((ltmp <=(- 32767 - 1)?(- 32767 - 1) : ltmp))));
    }

#pragma endscop
}
