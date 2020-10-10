#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int nb_bands;
extern unsigned int * restrict flags;
extern int  noref[9] ;
extern int  skip[9] ;

void loop()
{
#pragma scop

    for(i = nb_bands - 1; i >= 0; i--)
    {
        *flags <<= 1;
        *flags |=(noref[i] & 1);
        *flags <<= 1;
        *flags |=(skip[i] & 1);
    }

#pragma endscop
}
