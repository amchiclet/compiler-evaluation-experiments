#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern float suma;
extern float  a[32000] ;
extern float sumb;
extern float  b[32000] ;
extern float sumc;
extern float  c[32000] ;
extern float sumd;
extern float  d[32000] ;
extern float sume;
extern float  e[32000] ;

void loop()
{
#pragma scop

    for(int i = 0; i < 32000; i++)
    {
        suma += a[i];
        sumb += b[i];
        sumc += c[i];
        sumd += d[i];
        sume += e[i];
    }

#pragma endscop
}
