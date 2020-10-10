#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern double * restrict bark;
extern int cbase;
extern int cbands;
extern int * restrict cbandindex;
extern int  partition[513] ;
extern int  numlines[513] ;

void loop()
{
#pragma scop

    for(i = 1; i < 513; i++)
    {
        if(bark[i] - bark[cbase] > 1.0)
        {
            cbase = i;
            cbands++;
            cbandindex[cbands] = cbase;
        }
        partition[i] = cbands;
        numlines[cbands]++;
    }

#pragma endscop
}
