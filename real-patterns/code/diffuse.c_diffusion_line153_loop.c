#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int im;
extern int nmor;
extern double  ppmor[92700] ;
extern double  tmmor[92700] ;
extern double cona;
extern double  pmorx[92700] ;

void loop()
{
#pragma scop

    for(im = 0; im < nmor; im++)
    {
        ppmor[im] = ppmor[im] * tmmor[im];
        cona = cona + pmorx[im] * ppmor[im];
    }

#pragma endscop
}
