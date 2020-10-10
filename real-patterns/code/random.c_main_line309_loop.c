#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
typedef long long s64Int;
extern s64Int j;
extern int nstarts;
extern s64Int i;
extern s64Int nupdate;
typedef unsigned long long u64Int;
extern u64Int * restrict ran;
extern s64Int index;
extern s64Int tablesize;
extern u64Int * restrict Table;

void loop()
{
#pragma scop

    for(j = 0; j < nstarts; j++)
    {
        for(i = 0; i < nupdate /(nstarts * 2); i++)
        {
            ran[j] = ran[j] << 1 ^((((s64Int )ran[j]) < 0?0x0000000000000007ULL : 0));
            index =(ran[j] &(tablesize - 1));
            Table[index] ^= ran[j];
        }
    }

#pragma endscop
}
