#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
typedef unsigned long long BITBOARD;
extern BITBOARD  mask_no_pawn_attacks_w[64] ;
extern BITBOARD  minus8dir[65] ;
extern BITBOARD  mask_no_pawn_attacks_b[64] ;
extern BITBOARD  plus8dir[65] ;

void loop()
{
#pragma scop

    for(i = 8; i < 56; i++)
    {
        if(!(i & 7))
        {
            mask_no_pawn_attacks_w[i] = minus8dir[i + 1];
            mask_no_pawn_attacks_b[i] = plus8dir[i + 1];
        }
        else if((i & 7) == 7)
        {
            mask_no_pawn_attacks_w[i] = minus8dir[i - 1];
            mask_no_pawn_attacks_b[i] = plus8dir[i - 1];
        }
        else
        {
            mask_no_pawn_attacks_w[i] = minus8dir[i - 1] | minus8dir[i + 1];
            mask_no_pawn_attacks_b[i] = plus8dir[i + 1] | plus8dir[i - 1];
        }
    }

#pragma endscop
}
