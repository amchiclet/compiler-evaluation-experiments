#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
typedef unsigned long long BITBOARD;
extern BITBOARD  bishop_attacks_rl45[64][256] ;
extern int square;
extern int  bishop_mobility_rl45[64][256] ;

void loop()
{
#pragma scop

    for(i = 0; i < 256; i++)
    {
        bishop_attacks_rl45[square][i] = 0;
        bishop_mobility_rl45[square][i] = 0;
    }

#pragma endscop
}
