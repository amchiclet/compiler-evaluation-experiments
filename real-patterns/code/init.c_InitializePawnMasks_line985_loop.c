#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
typedef unsigned long long BITBOARD;
extern BITBOARD  mask_pawn_isolated[64] ;
extern BITBOARD  file_mask[8] ;

void loop()
{
#pragma scop

    for(i = 0; i < 64; i++)
    {
        if(!(i & 7)) mask_pawn_isolated[i] = file_mask[(i & 7) + 1];
        else if((i & 7) == 7) mask_pawn_isolated[i] = file_mask[(i & 7) - 1];
        else mask_pawn_isolated[i] = file_mask[(i & 7) - 1] | file_mask[(i & 7) + 1];
    }

#pragma endscop
}
