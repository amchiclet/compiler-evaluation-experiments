#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int nmor;
extern double  tmort[92700] ;
extern double  mormult[92700] ;

void loop()
{
#pragma scop

    for(i = 0; i < nmor; i++)
    {
        tmort[i] = tmort[i] / mormult[i];
    }

#pragma endscop
}
