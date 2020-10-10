#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
typedef unsigned int JDIMENSION;
extern JDIMENSION col;
extern JDIMENSION num_cols;
extern int r;
typedef unsigned char JSAMPLE;
typedef JSAMPLE *JSAMPROW;
extern  __restrict__ JSAMPROW inptr;
extern int g;
extern int b;
extern  __restrict__ JSAMPROW outptr3;
extern  __restrict__ JSAMPROW outptr0;
typedef long JLONG;
extern JLONG * __restrict__ ctab;
extern  __restrict__ JSAMPROW outptr1;
extern  __restrict__ JSAMPROW outptr2;

void loop()
{
  int __col_0__ = col;
  
#pragma scop
  for (__col_0__ = 0; __col_0__ <= num_cols - 1; __col_0__ += 1) {
    r = 255 - ((int )inptr[0]);
    g = 255 - ((int )inptr[1]);
    b = 255 - ((int )inptr[2]);
    outptr3[__col_0__] = inptr[3];
    inptr += 4;
    outptr0[__col_0__] = ((JSAMPLE )(ctab[r + 0] + ctab[g + 1 * (255 + 1)] + ctab[b + 2 * (255 + 1)] >> 16));
    outptr1[__col_0__] = ((JSAMPLE )(ctab[r + 3 * (255 + 1)] + ctab[g + 4 * (255 + 1)] + ctab[b + 5 * (255 + 1)] >> 16));
    outptr2[__col_0__] = ((JSAMPLE )(ctab[r + 5 * (255 + 1)] + ctab[g + 6 * (255 + 1)] + ctab[b + 7 * (255 + 1)] >> 16));
  }
  
#pragma endscop
  col = __col_0__;
}
