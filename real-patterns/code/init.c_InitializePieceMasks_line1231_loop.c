#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
typedef unsigned long long BITBOARD;
extern BITBOARD  white_pawn_race_wtm[64] ;
extern BITBOARD  white_pawn_race_btm[64] ;
extern BITBOARD  black_pawn_race_wtm[64] ;
extern BITBOARD  black_pawn_race_btm[64] ;

void loop()
{
#pragma scop

    for(i = 0; i < 64; i++)
    {
        white_pawn_race_wtm[i] = 0;
        white_pawn_race_btm[i] = 0;
        black_pawn_race_wtm[i] = 0;
        black_pawn_race_btm[i] = 0;
    }

#pragma endscop
}
