#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
typedef long long s64Int;
extern s64Int i;
extern s64Int tablesize;
typedef unsigned long long u64Int;
extern u64Int * restrict Table;

void loop()
{
#pragma scop

    for(i = 0; i < tablesize; i++) Table[i] =((u64Int )i);

#pragma endscop
}
