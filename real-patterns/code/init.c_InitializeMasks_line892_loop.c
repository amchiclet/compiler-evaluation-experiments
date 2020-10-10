#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
typedef unsigned long long BITBOARD;
extern BITBOARD  clear_mask[65] ;
extern BITBOARD mask_1;
extern BITBOARD  clear_mask_rl45[65] ;
extern int  init_l45[64] ;
extern BITBOARD  clear_mask_rr45[65] ;
extern int  init_r45[64] ;
extern BITBOARD  clear_mask_rl90[65] ;
extern int  init_l90[64] ;
extern BITBOARD  set_mask[65] ;
extern BITBOARD  set_mask_rl45[65] ;
extern BITBOARD  set_mask_rr45[65] ;
extern BITBOARD  set_mask_rl90[65] ;

void loop()
{
#pragma scop

    for(i = 0; i < 64; i++)
    {
        clear_mask[i] = ~(mask_1 >> i);
        clear_mask_rl45[i] = ~(mask_1 >> init_l45[i]);
        clear_mask_rr45[i] = ~(mask_1 >> init_r45[i]);
        clear_mask_rl90[i] = ~(mask_1 >> init_l90[i]);
        set_mask[i] = mask_1 >> i;
        set_mask_rl45[i] = mask_1 >> init_l45[i];
        set_mask_rr45[i] = mask_1 >> init_r45[i];
        set_mask_rl90[i] = mask_1 >> init_l90[i];
    }

#pragma endscop
}
