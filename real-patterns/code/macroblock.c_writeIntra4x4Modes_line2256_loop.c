#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int block8x8;
typedef long long int64;
struct macroblock
{
    int currSEnr;
    int slice_nr;
    int delta_qp;
    int qp;
    int qpsp;
    struct macroblock *mb_available_up;
    struct macroblock *mb_available_left;
    int mb_type;
    int mvd[2][16 / 4][16 / 4][2];
    char intra_pred_modes[16 / 4 *(16 / 4)];
    char intra_pred_modes8x8[16 / 4 *(16 / 4)];
    int cbp;
    int64 cbp_blk;
    int b8mode[4];
    int b8pdir[4];
    int64 cbp_bits;
    int c_ipred_mode;
    int IntraChromaPredModeFlag;
    int mb_field;
    int list_offset;
    int mbAddrA;
    int mbAddrB;
    int mbAddrC;
    int mbAddrD;
    int mbAvailA;
    int mbAvailB;
    int mbAvailC;
    int mbAvailD;
    int all_blk_8x8;
    int luma_transform_size_8x8_flag;
    int NoMbPartLessThan8x8Flag;
    short bi_pred_me;
    double actj;
    int prev_qp;
    int prev_delta_qp;
    int prev_cbp;
    int predict_qp;
    int predict_error;
    int LFDisableIdc;
    int LFAlphaC0Offset;
    int LFBetaOffset;
    int skip_flag;
};

typedef struct macroblock  Macroblock;
extern Macroblock * restrict currMB;
extern int only_this_block;
extern int bs_x;
extern int bs_y;
extern int ii;
extern int jj;
extern int j;
extern int i;
extern char  ipred_array[16] ;
extern int ipred_number;
extern int  cont_array[16] ;

void loop()
{
#pragma scop

    for(block8x8 = 0; block8x8 < 4; block8x8++)
    {
        if(currMB -> b8mode[block8x8] == 11 &&(only_this_block < 0 || only_this_block == block8x8) || currMB -> b8mode[block8x8] == 13 &&(only_this_block < 0 || only_this_block == block8x8))
        {
            bs_x = bs_y =(currMB -> b8mode[block8x8] == 13?8 : 4);
            ii = bs_x >> 2;
            jj = bs_y >> 2;
            for(j = 0; j < 4; j += jj << 1)
            {
                for(i = 0; i < 2; i += ii)
                {
                    ipred_array[ipred_number] = currMB -> intra_pred_modes[block8x8 << 2 | j | i];
                    cont_array[ipred_number] =(block8x8 << 2) + j + i;
                    ipred_number++;
                }
            }
        }
    }

#pragma endscop
}
