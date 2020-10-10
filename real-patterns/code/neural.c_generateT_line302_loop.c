#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int row;
extern int NNTOT;
extern int col;
typedef float real;
extern real ** restrict Tmatrix;

void loop()
{
#pragma scop

    for(row = 0; row < NNTOT; row++) for(col = 0; col < NNTOT; col++) Tmatrix[row][col] = 0.0;

#pragma endscop
}
