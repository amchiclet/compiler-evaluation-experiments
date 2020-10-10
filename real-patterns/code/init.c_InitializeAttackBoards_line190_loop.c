#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
typedef unsigned long long BITBOARD;
extern BITBOARD  w_pawn_attacks[64] ;
extern int j;
extern int sq;
extern int  bishopsq[4] ;
extern BITBOARD mask_1;
extern BITBOARD  b_pawn_attacks[64] ;

void loop()
{
#pragma scop

    for(i = 0; i < 64; i++)
    {
        w_pawn_attacks[i] = 0;
        if(i < 56) for(j = 2; j < 4; j++)
            {
                sq = i + bishopsq[j];
                if(abs(sq / 8 - i / 8) == 1 && abs((sq & 7) -(i & 7)) == 1 && sq < 64 && sq > - 1) w_pawn_attacks[i] = w_pawn_attacks[i] | mask_1 >> sq;
            }
        b_pawn_attacks[i] = 0;
        if(i > 7) for(j = 0; j < 2; j++)
            {
                sq = i + bishopsq[j];
                if(abs(sq / 8 - i / 8) == 1 && abs((sq & 7) -(i & 7)) == 1 && sq < 64 && sq > - 1) b_pawn_attacks[i] = b_pawn_attacks[i] | mask_1 >> sq;
            }
    }

#pragma endscop
}
