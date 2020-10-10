#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int code;
extern int  base_length[29] ;
extern int length;
extern int n;
extern int  extra_lbits[29] ;
typedef unsigned char uch;
extern uch  length_code[258 - 3 + 1] ;

void loop()
{
#pragma scop

    for(code = 0; code < 29 - 1; code++)
    {
        base_length[code] = length;
        for(n = 0; n < 1 << extra_lbits[code]; n++)
        {
            length_code[length++] =((uch )code);
        }
    }

#pragma endscop
}
