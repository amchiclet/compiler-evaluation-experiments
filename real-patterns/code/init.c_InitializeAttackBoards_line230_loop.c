#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
typedef unsigned long long BITBOARD;
extern BITBOARD  bishop_attacks[64] ;
extern int j;
extern int sq;
extern int lastsq;
extern int  bishopsq[4] ;
extern BITBOARD mask_1;
extern BITBOARD  queen_attacks[64] ;
extern BITBOARD  plus7dir[65] ;
extern BITBOARD  plus9dir[65] ;
extern BITBOARD  minus7dir[65] ;
extern BITBOARD  minus9dir[65] ;

void loop()
{
#pragma scop

    for(i = 0; i < 64; i++)
    {
        bishop_attacks[i] = 0;
        for(j = 0; j < 4; j++)
        {
            sq = i;
            lastsq = sq;
            sq = sq + bishopsq[j];
            while(abs(sq / 8 - lastsq / 8) == 1 && abs((sq & 7) -(lastsq & 7)) == 1 && sq < 64 && sq > - 1)
            {
                bishop_attacks[i] = bishop_attacks[i] | mask_1 >> sq;
                queen_attacks[i] = queen_attacks[i] | mask_1 >> sq;
                if(bishopsq[j] == 7) plus7dir[i] = plus7dir[i] | mask_1 >> sq;
                else if(bishopsq[j] == 9) plus9dir[i] = plus9dir[i] | mask_1 >> sq;
                else if(bishopsq[j] == - 7) minus7dir[i] = minus7dir[i] | mask_1 >> sq;
                else minus9dir[i] = minus9dir[i] | mask_1 >> sq;
                lastsq = sq;
                sq = sq + bishopsq[j];
            }
        }
    }

#pragma endscop
}
