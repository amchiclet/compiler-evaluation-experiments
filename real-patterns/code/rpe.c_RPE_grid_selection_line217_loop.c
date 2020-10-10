#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
typedef short word;
extern word * restrict xM;
extern word * restrict x;
extern word Mc;

void loop()
{
#pragma scop

    for(i = 0; i <= 12; i++) xM[i] = x[Mc + 3 * i];

#pragma endscop
}
