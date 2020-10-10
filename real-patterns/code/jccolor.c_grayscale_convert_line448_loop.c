#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
typedef unsigned int JDIMENSION;
extern JDIMENSION col;
extern JDIMENSION num_cols;
typedef unsigned char JSAMPLE;
typedef JSAMPLE * JSAMPROW;
extern JSAMPROW restrict outptr;
extern JSAMPROW restrict inptr;
extern int instride;

void loop()
{
#pragma scop

    for(col = 0; col < num_cols; col++)
    {
        outptr[col] = inptr[0];
        inptr += instride;
    }

#pragma endscop
}
