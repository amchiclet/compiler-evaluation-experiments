#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int a;
typedef long int64_t;
extern int  dev_4_3_coefs[13] ;

void loop()
{
#pragma scop

    for(i = 0; i < 13; i++)
    {
        a =((((int64_t )a) *((int64_t )(((int )(4.0 / 3.0 *(1 << 24))) - i *((int )(1.0 *(1 << 24))))) >> 24) /(i + 1));
        dev_4_3_coefs[i] = a;
    }

#pragma endscop
}
