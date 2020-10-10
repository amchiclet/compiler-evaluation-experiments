#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
typedef int I32;
extern I32 Class;
extern char * restrict opnd;

void loop()
{
#pragma scop

    for(Class = 0; Class < 256; Class++) if(Class >= 65 && Class <= 'Z' || Class >= 'a' && Class <= 'z' || Class >= 48 && Class <= 57 || Class == '_') opnd[1 +(Class >> 3 & 31)] |= 1 <<(Class & 7);

#pragma endscop
}
