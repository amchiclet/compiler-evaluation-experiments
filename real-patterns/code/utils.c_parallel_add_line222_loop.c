#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int nellog;
extern int n1;
extern int ntemp;
extern int n2;
extern int iel;
extern int nelt;
extern int ahead;
extern int* restrict frontier;
extern int ii;
extern int ntemp1;

void loop()
{
#pragma scop

    for(i = 0; i < nellog; i++)
    {
        n1 = ntemp * 2;
        n2 = n1;
        for(iel = n1; iel <= nelt; iel += n1)
        {
            ahead = frontier[iel - ntemp - 1];
            for(ii = ntemp - 1; ii >= 0; ii--)
            {
                frontier[iel - ii - 1] = frontier[iel - ii - 1] + ahead;
            }
            n2 = iel;
        }
        if(n2 <= nelt) n2 = n2 + n1;
        ntemp1 = n2 - nelt;
        if(ntemp1 < ntemp)
        {
            ahead = frontier[n2 - ntemp - 1];
            for(ii = ntemp - 1; ii >= ntemp1; ii--)
            {
                frontier[n2 - ii - 1] = frontier[n2 - ii - 1] + ahead;
            }
        }
        ntemp = n1;
    }

#pragma endscop
}
