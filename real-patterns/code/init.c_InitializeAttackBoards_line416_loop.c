#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
typedef unsigned long long BITBOARD;
extern BITBOARD  rook_attacks_r0[64][256] ;
extern int square;
extern int  rook_mobility_r0[64][256] ;

void loop()
{
#pragma scop

    for(i = 0; i < 256; i++)
    {
        rook_attacks_r0[square][i] = 0;
        rook_mobility_r0[square][i] = 0;
    }

#pragma endscop
}
