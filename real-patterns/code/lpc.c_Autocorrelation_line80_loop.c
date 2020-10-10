#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
typedef short word;
extern word * restrict s;
typedef long longword;

void loop()
{
#pragma scop

    for(k = 0; k <= 159; k++) s[k] =(((longword )s[k]) *((longword )(16384 >> 1 - 1)) + 16384 >> 15);

#pragma endscop
}
