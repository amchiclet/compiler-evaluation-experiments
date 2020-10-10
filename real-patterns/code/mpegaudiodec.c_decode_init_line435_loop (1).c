#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern float  ci_table[8] ;
extern int32_t  csa_table[8][4] ;
extern float  csa_table_float[8][4] ;

void loop()
{
#pragma scop

    for(i = 0; i < 8; i++)
    {
        float ci;
        float cs;
        float ca;
        ci = ci_table[i];
        cs =(1.0 / sqrt(1.0 +(ci * ci)));
        ca = cs * ci;
        csa_table[i][0] =((int )((cs / 4 *(1LL << 32)) + 0.5));
        csa_table[i][1] =((int )((ca / 4 *(1LL << 32)) + 0.5));
        csa_table[i][2] =((int )((ca / 4 *(1LL << 32)) + 0.5)) +((int )((cs / 4 *(1LL << 32)) + 0.5));
        csa_table[i][3] =((int )((ca / 4 *(1LL << 32)) + 0.5)) -((int )((cs / 4 *(1LL << 32)) + 0.5));
        csa_table_float[i][0] = cs;
        csa_table_float[i][1] = ca;
        csa_table_float[i][2] = ca + cs;
        csa_table_float[i][3] = ca - cs;
    }

#pragma endscop
}
