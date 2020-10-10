#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
typedef long longword;
extern longword L_result;
typedef short word;
extern word * restrict e;
extern word * restrict x;

void loop()
{
#pragma scop

    for(k = 0; k <= 39; k++)
    {
        L_result =(8192 >> 1);
        L_result += e[k + 0] *((longword )(- 134)) + e[k + 1] *((longword )(- 374)) + e[k + 3] *((longword )2054) + e[k + 4] *((longword )5741) + e[k + 5] *((longword )8192) + e[k + 6] *((longword )5741) + e[k + 7] *((longword )2054) + e[k + 9] *((longword )(- 374)) + e[k + 10] *((longword )(- 134));
        L_result = L_result >> 13;
        x[k] =((L_result <(- 32767 - 1)?(- 32767 - 1) :((L_result > 32767?32767 : L_result))));
    }

#pragma endscop
}
