#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
typedef unsigned long long BITBOARD;
extern BITBOARD  knight_attacks[64] ;
extern int frank;
extern int ffile;
extern int j;
extern int sq;
extern int  knightsq[8] ;
extern int trank;
extern int tfile;
extern BITBOARD mask_1;

void loop()
{
#pragma scop

    for(i = 0; i < 64; i++)
    {
        knight_attacks[i] = 0;
        frank = i / 8;
        ffile = i & 7;
        for(j = 0; j < 8; j++)
        {
            sq = i + knightsq[j];
            if(sq < 0 || sq > 63) continue;
            trank = sq / 8;
            tfile = sq & 7;
            if(abs(frank - trank) > 2 || abs(ffile - tfile) > 2) continue;
            knight_attacks[i] = knight_attacks[i] | mask_1 >> sq;
        }
    }

#pragma endscop
}
