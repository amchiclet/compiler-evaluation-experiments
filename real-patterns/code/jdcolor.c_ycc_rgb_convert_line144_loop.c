#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
typedef unsigned int JDIMENSION;
extern JDIMENSION col;
extern JDIMENSION num_cols;
extern int y;
typedef unsigned char JSAMPLE;
typedef JSAMPLE * JSAMPROW;
extern JSAMPROW restrict inptr0;
extern int cb;
extern JSAMPROW restrict inptr1;
extern int cr;
extern JSAMPROW restrict inptr2;
extern JSAMPROW restrict outptr;
extern JSAMPLE * restrict range_limit;
extern int * restrict Crrtab;
typedef long INT32;
extern INT32 * restrict Cbgtab;
extern INT32 * restrict Crgtab;
extern int * restrict Cbbtab;

void loop()
{
#pragma scop

    for(col = 0; col < num_cols; col++)
    {
        y =((int )inptr0[col]);
        cb =((int )inptr1[col]);
        cr =((int )inptr2[col]);
        outptr[0] = range_limit[y + Crrtab[cr]];
        outptr[1] = range_limit[y +((int )(Cbgtab[cb] + Crgtab[cr] >> 16))];
        outptr[2] = range_limit[y + Cbbtab[cb]];
        outptr += 3;
    }

#pragma endscop
}
