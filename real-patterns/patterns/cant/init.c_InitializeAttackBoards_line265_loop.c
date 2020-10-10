#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
typedef unsigned long long BITBOARD;
extern BITBOARD  rook_attacks[64] ;
extern int j;
extern int sq;
extern int lastsq;
extern int  rooksq[4] ;
extern BITBOARD mask_1;
extern BITBOARD  queen_attacks[64] ;
extern BITBOARD  plus1dir[65] ;
extern BITBOARD  plus8dir[65] ;
extern BITBOARD  minus1dir[65] ;
extern BITBOARD  minus8dir[65] ;

void loop()
{
#pragma scop

    for(i = 0; i < 64; i++)
    {
        rook_attacks[i] = 0;
        for(j = 0; j < 4; j++)
        {
            sq = i;
            lastsq = sq;
            sq = sq + rooksq[j];
            while((abs(sq / 8 - lastsq / 8) == 1 && abs((sq & 7) -(lastsq & 7)) == 0 || abs(sq / 8 - lastsq / 8) == 0 && abs((sq & 7) -(lastsq & 7)) == 1) && sq < 64 && sq > - 1)
            {
                rook_attacks[i] = rook_attacks[i] | mask_1 >> sq;
                queen_attacks[i] = queen_attacks[i] | mask_1 >> sq;
                if(rooksq[j] == 1) plus1dir[i] = plus1dir[i] | mask_1 >> sq;
                else if(rooksq[j] == 8) plus8dir[i] = plus8dir[i] | mask_1 >> sq;
                else if(rooksq[j] == - 1) minus1dir[i] = minus1dir[i] | mask_1 >> sq;
                else minus8dir[i] = minus8dir[i] | mask_1 >> sq;
                lastsq = sq;
                sq = sq + rooksq[j];
            }
        }
    }

#pragma endscop
}
