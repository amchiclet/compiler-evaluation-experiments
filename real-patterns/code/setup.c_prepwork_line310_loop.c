#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
extern int iel;
extern int nelt;
extern int  size_e[2400] ;
extern double  xc[2400][8] ;
extern double rdlog2;

void loop()
{
#pragma scop

    for(iel = 0; iel < nelt; iel++)
    {
        size_e[iel] =((int )(-log(xc[iel][1] - xc[iel][0]) * rdlog2 + 1.e-8)) - 1;
    }

#pragma endscop
}
