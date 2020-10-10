#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int im;
extern int nmor;
extern double  pmorx[92700] ;
extern double  dpcmor[92700] ;
extern double  rmor[92700] ;
extern double rho1;

void loop()
{
#pragma scop

    for(im = 0; im < nmor; im++)
    {
        pmorx[im] = dpcmor[im] * rmor[im];
        rho1 = rho1 + rmor[im] * pmorx[im];
    }

#pragma endscop
}
