#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
typedef unsigned long long BITBOARD;
typedef struct
{
    BITBOARD w_occupied;
    BITBOARD b_occupied;
    BITBOARD occupied_rl90;
    BITBOARD occupied_rl45;
    BITBOARD occupied_rr45;
    BITBOARD rooks_queens;
    BITBOARD bishops_queens;
    BITBOARD w_pawn;
    BITBOARD w_knight;
    BITBOARD w_bishop;
    BITBOARD w_rook;
    BITBOARD w_queen;
    BITBOARD b_pawn;
    BITBOARD b_knight;
    BITBOARD b_bishop;
    BITBOARD b_rook;
    BITBOARD b_queen;
    BITBOARD hash_key;
    unsigned int pawn_hash_key;
    int material_evaluation;
    signed char white_king;
    signed char black_king;
    signed char board[64];
    signed char white_pieces;
    signed char white_pawns;
    signed char black_pieces;
    signed char black_pawns;
    signed char total_pieces;
} CHESS_POSITION;
extern struct
{
    BITBOARD w_occupied;
    BITBOARD b_occupied;
    BITBOARD occupied_rl90;
    BITBOARD occupied_rl45;
    BITBOARD occupied_rr45;
    BITBOARD rooks_queens;
    BITBOARD bishops_queens;
    BITBOARD w_pawn;
    BITBOARD w_knight;
    BITBOARD w_bishop;
    BITBOARD w_rook;
    BITBOARD w_queen;
    BITBOARD b_pawn;
    BITBOARD b_knight;
    BITBOARD b_bishop;
    BITBOARD b_rook;
    BITBOARD b_queen;
    BITBOARD hash_key;
    unsigned int pawn_hash_key;
    int material_evaluation;
    signed char white_king;
    signed char black_king;
    signed char board[64];
    signed char white_pieces;
    signed char white_pawns;
    signed char black_pieces;
    signed char black_pawns;
    signed char total_pieces;
} search;
extern BITBOARD  set_mask_rl90[65] ;
extern BITBOARD  set_mask_rl45[65] ;
extern BITBOARD  set_mask_rr45[65] ;

void loop()
{
#pragma scop

    for(i = 0; i < 64; i++)
    {
        if(search . board[i])
        {
            search . occupied_rl90 = search . occupied_rl90 | set_mask_rl90[i];
            search . occupied_rl45 = search . occupied_rl45 | set_mask_rl45[i];
            search . occupied_rr45 = search . occupied_rr45 | set_mask_rr45[i];
        }
    }

#pragma endscop
}
