#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
typedef unsigned int png_uint_32;
extern png_uint_32 i;
extern png_uint_32 row_width;
typedef unsigned char png_byte;
typedef png_byte * png_bytep;
extern png_bytep restrict sp;
typedef const png_byte * png_const_bytep;
extern png_const_bytep restrict gamma_table;

void loop()
{
#pragma scop

    for(i = 0; i < row_width; i++)
    {
        *sp = gamma_table[ *sp];
        sp++;
    }

#pragma endscop
}
