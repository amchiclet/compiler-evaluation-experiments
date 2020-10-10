#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
typedef unsigned long size_t;
typedef size_t png_size_t;
extern png_size_t i;
extern png_size_t istop;
typedef unsigned char png_byte;
typedef png_byte * png_bytep;
extern png_bytep restrict rp;

void loop()
{
#pragma scop

    for(i = 0; i < istop; i += 4)
    {
        *rp =((png_byte )(~( *rp)));
        *(rp + 1) =((png_byte )(~( *(rp + 1))));
        rp += 4;
    }

#pragma endscop
}
