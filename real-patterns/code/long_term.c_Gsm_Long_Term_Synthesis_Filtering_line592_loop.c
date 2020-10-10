#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
typedef short word;
extern word drpp;
typedef long longword;
extern word brp;
extern word * restrict drp;
extern word Nr;
typedef unsigned long ulongword;
extern longword ltmp;
extern word * restrict erp;

void loop()
{
#pragma scop

    for(k = 0; k <= 39; k++)
    {
        drpp =(((longword )brp) *((longword )drp[k - Nr]) + 16384 >> 15);
        drp[k] =((((ulongword )((ltmp =((longword )erp[k]) +((longword )drpp)) -(- 32767 - 1))) >(32767 -(- 32767 - 1))?((ltmp > 0?32767 : - 32767 - 1)) : ltmp));
    }

#pragma endscop
}
