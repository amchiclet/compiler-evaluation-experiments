#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
typedef unsigned long long BITBOARD;
extern BITBOARD  mask_pawn_connected[64] ;
extern BITBOARD  set_mask[65] ;

void loop()
{
#pragma scop

    for(i = 8; i < 56; i++)
    {
        if((i & 7) > 0 &&(i & 7) < 7) mask_pawn_connected[i] = set_mask[i - 9] | set_mask[i - 7] | set_mask[i - 1] | set_mask[i + 1] | set_mask[i + 7] | set_mask[i + 9];
        else if((i & 7) == 0) mask_pawn_connected[i] = set_mask[i - 7] | set_mask[i + 1] | set_mask[i + 9];
        else if((i & 7) == 7) mask_pawn_connected[i] = set_mask[i - 9] | set_mask[i - 1] | set_mask[i + 7];
    }

#pragma endscop
}
