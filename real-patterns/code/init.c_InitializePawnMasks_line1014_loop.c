#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
typedef unsigned long long BITBOARD;
extern BITBOARD  mask_pawn_passed_w[64] ;
extern BITBOARD  plus8dir[65] ;
extern BITBOARD  mask_pawn_passed_b[64] ;
extern BITBOARD  minus8dir[65] ;

void loop()
{
#pragma scop

    for(i = 0; i < 64; i++)
    {
        if(!(i & 7))
        {
            mask_pawn_passed_w[i] = plus8dir[i] | plus8dir[i + 1];
            mask_pawn_passed_b[i] = minus8dir[i] | minus8dir[i + 1];
        }
        else if((i & 7) == 7)
        {
            mask_pawn_passed_w[i] = plus8dir[i - 1] | plus8dir[i];
            mask_pawn_passed_b[i] = minus8dir[i - 1] | minus8dir[i];
        }
        else
        {
            mask_pawn_passed_w[i] = plus8dir[i - 1] | plus8dir[i] | plus8dir[i + 1];
            mask_pawn_passed_b[i] = minus8dir[i - 1] | minus8dir[i] | minus8dir[i + 1];
        }
    }

#pragma endscop
}
