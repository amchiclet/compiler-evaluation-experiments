#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
typedef unsigned long long BITBOARD;
extern BITBOARD  mask_pawn_protected_w[64] ;
extern BITBOARD  set_mask[65] ;
extern BITBOARD  mask_pawn_protected_b[64] ;

void loop()
{
#pragma scop

    for(i = 8; i < 56; i++)
    {
        mask_pawn_protected_w[i] = set_mask[i - 1] | set_mask[i + 1];
        if(i > 15) mask_pawn_protected_w[i] |= set_mask[i - 7] | set_mask[i - 9];
        mask_pawn_protected_b[i] = set_mask[i - 1] | set_mask[i + 1];
        if(i < 48) mask_pawn_protected_b[i] |= set_mask[i + 7] | set_mask[i + 9];
    }

#pragma endscop
}
