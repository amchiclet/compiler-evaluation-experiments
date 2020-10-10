#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
typedef int I32;
extern I32 Class;
extern char * restrict opnd;

void loop()
{
#pragma scop

    for(Class = 0; Class < 256; Class++) if(Class == 32 || Class == 9 || Class == 10 || Class == 13 || Class == 12) opnd[1 +(Class >> 3 & 31)] |= 1 <<(Class & 7);

#pragma endscop
}
