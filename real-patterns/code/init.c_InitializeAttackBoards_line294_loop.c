#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
typedef unsigned long long BITBOARD;
extern BITBOARD  king_attacks[64] ;
extern BITBOARD  king_attacks_1[64] ;
extern BITBOARD  king_attacks_2[64] ;
extern int j;
extern BITBOARD  set_mask[65] ;

void loop()
{
#pragma scop

    for(i = 0; i < 64; i++)
    {
        king_attacks[i] = 0;
        king_attacks_1[i] = 0;
        king_attacks_2[i] = 0;
        for(j = 0; j < 64; j++)
        {
            if(((abs((i & 7) -(j & 7)) > abs((i >> 3) -(j >> 3))?abs((i & 7) -(j & 7)) : abs((i >> 3) -(j >> 3)))) == 1) king_attacks[i] = king_attacks[i] | set_mask[j];
            if(((abs((i & 7) -(j & 7)) > abs((i >> 3) -(j >> 3))?abs((i & 7) -(j & 7)) : abs((i >> 3) -(j >> 3)))) <= 1) king_attacks_1[i] = king_attacks_1[i] | set_mask[j];
            if(((abs((i & 7) -(j & 7)) > abs((i >> 3) -(j >> 3))?abs((i & 7) -(j & 7)) : abs((i >> 3) -(j >> 3)))) <= 2) king_attacks_2[i] = king_attacks_2[i] | set_mask[j];
        }
    }

#pragma endscop
}
