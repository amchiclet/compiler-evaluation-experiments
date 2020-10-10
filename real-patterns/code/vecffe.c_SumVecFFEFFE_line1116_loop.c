#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern unsigned long i;
extern unsigned long len;
typedef unsigned short TypFFE;
extern TypFFE vL;
struct TypHeader
{
    unsigned long size;
    struct TypHeader **ptr;
    char name[3];
    unsigned char type;
};

typedef struct TypHeader* TypHandle;
extern struct TypHeader* restrict hdL;
extern struct TypHeader* restrict hdS;
extern TypFFE vR;
extern TypFFE * restrict fld;

void loop()
{
#pragma scop

    for(i = 1; i <= len; i++)
    {
        vL =((TypFFE *)(((TypHandle *)(hdL -> ptr)) + 1))[i - 1];
        ((TypFFE *)(((TypHandle *)(hdS -> ptr)) + 1))[i - 1] =((vL == 0 || vR == 0?vL + vR :((vL <= vR?((vL == 0 || fld[vR - vL + 1] == 0?0 :((vL - 1 <=( *fld) - fld[vR - vL + 1]?vL - 1 + fld[vR - vL + 1] : vL - 1 -(( *fld) - fld[vR - vL + 1]))))) :((vR == 0 || fld[vL - vR + 1] == 0?0 :((vR - 1 <=( *fld) - fld[vL - vR + 1]?vR - 1 + fld[vL - vR + 1] : vR - 1 -(( *fld) - fld[vL - vR + 1])))))))));
    }

#pragma endscop
}
