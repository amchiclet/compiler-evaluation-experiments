#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern double  LTtm[136] ;
extern double  LTnm[136] ;

void loop()
{
#pragma scop

    for(i = 0; i < 136; i++)
    {
        LTtm[i] = - 200.0;
        LTnm[i] = - 200.0;
    }

#pragma endscop
}
