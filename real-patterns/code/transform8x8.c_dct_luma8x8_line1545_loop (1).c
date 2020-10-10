#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int  a[8] ;
typedef unsigned char byte;
typedef struct
{
    int byte_pos;
    int bits_to_go;
    byte byte_buf;
    int stored_byte_pos;
    int stored_bits_to_go;
    byte stored_byte_buf;
    byte byte_buf_skip;
    int byte_pos_skip;
    int bits_to_go_skip;
    byte *streamBuffer;
    int write_flag;
} Bitstream;
typedef struct
{
    unsigned int Elow;
    unsigned int Erange;
    unsigned int Ebuffer;
    unsigned int Ebits_to_go;
    unsigned int Ebits_to_follow;
    byte *Ecodestrm;
    int *Ecodestrm_len;
    int C;
    int E;
    unsigned int ElowS;
    unsigned int ErangeS;
    unsigned int EbufferS;
    unsigned int Ebits_to_goS;
    unsigned int Ebits_to_followS;
    byte *EcodestrmS;
    int *Ecodestrm_lenS;
    int CS;
    int ES;
} EncodingEnvironment;
struct datapartition
{
    Bitstream *bitstream;
    EncodingEnvironment ee_cabac;
};

typedef struct datapartition  DataPartition;
typedef struct
{
    unsigned short state;
    unsigned char MPS;
    unsigned long count;
} BiContextType;
typedef struct
{
    BiContextType mb_type_contexts[3][11];
    BiContextType b8_type_contexts[2][9];
    BiContextType mv_res_contexts[2][10];
    BiContextType ref_no_contexts[2][6];
    BiContextType delta_qp_contexts[4];
    BiContextType mb_aff_contexts[4];
    BiContextType transform_size_contexts[3];
} MotionInfoContexts;
typedef struct
{
    BiContextType ipr_contexts[2];
    BiContextType cipr_contexts[4];
    BiContextType cbp_contexts[3][4];
    BiContextType bcbp_contexts[10][4];
    BiContextType map_contexts[10][15];
    BiContextType last_contexts[10][15];
    BiContextType one_contexts[10][5];
    BiContextType abs_contexts[10][5];
    BiContextType fld_map_contexts[10][15];
    BiContextType fld_last_contexts[10][15];
} TextureInfoContexts;
struct RMPNIbuffer_s
{
    int RMPNI;
    int Data;
    struct RMPNIbuffer_s *Next;
};

typedef struct RMPNIbuffer_s  RMPNIbuffer_t;
typedef struct
{
    int picture_id;
    int qp;
    int picture_type;
    int start_mb_nr;
    int max_part_nr;
    int num_mb;
    DataPartition *partArr;
    MotionInfoContexts *mot_ctx;
    TextureInfoContexts *tex_ctx;
    RMPNIbuffer_t *rmpni_buffer;
    int ref_pic_list_reordering_flag_l0;
    int *reordering_of_pic_nums_idc_l0;
    int *abs_diff_pic_num_minus1_l0;
    int *long_term_pic_idx_l0;
    int ref_pic_list_reordering_flag_l1;
    int *reordering_of_pic_nums_idc_l1;
    int *abs_diff_pic_num_minus1_l1;
    int *long_term_pic_idx_l1;
    int field_ctx[3][2];
} Slice;
typedef struct
{
    int no_slices;
    int idr_flag;
    Slice *slices[100];
    int bits_per_picture;
    float distortion_y;
    float distortion_u;
    float distortion_v;
} Picture;
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
struct syntaxelement
{
    int type;
    int value1;
    int value2;
    int len;
    int inf;
    unsigned int bitpattern;
    int context;
    int k;
};

typedef struct syntaxelement  SyntaxElement;
struct DecRefPicMarking_s
{
    int memory_management_control_operation;
    int difference_of_pic_nums_minus1;
    int long_term_pic_num;
    int long_term_frame_idx;
    int max_long_term_frame_idx_plus1;
    struct DecRefPicMarking_s *Next;
};

typedef struct DecRefPicMarking_s  DecRefPicMarking_t;
typedef struct
{
    int number;
    int pn;
    int LevelIndex;
    int current_mb_nr;
    int total_number_mb;
    int current_slice_nr;
    int type;
    int structure;
    int num_ref_frames;
    int max_num_references;
    int qp;
    int qpsp;
    float framerate;
    int width;
    int width_cr;
    int height;
    int height_cr;
    int height_cr_frame;
    int subblock_x;
    int subblock_y;
    int is_intra_block;
    int is_v_block;
    int mb_y_upd;
    int mb_y_intra;
    int block_c_x;
    char **ipredmode;
    char **ipredmode8x8;
    int cod_counter;
    int ***nz_coeff;
    int mb_x;
    int mb_y;
    int block_x;
    int block_y;
    int pix_x;
    int pix_y;
    int pix_c_x;
    int pix_c_y;
    int opix_x;
    int opix_y;
    int opix_c_x;
    int opix_c_y;
    unsigned short mprr[9][16][16];
    unsigned short mprr_2[5][16][16];
    unsigned short mprr_3[9][8][8];
    unsigned short mprr_c[2][4][16][16];
    unsigned short mpr[16][16];
    int m7[16][16];
    int ****cofAC;
    int ***cofDC;
    int fadjust4x4[4][16][16];
    int fadjust8x8[3][16][16];
    int fadjust4x4Cr[4][2][16][16];
    int fadjust8x8Cr[1][2][16][16];
    Picture *currentPicture;
    Slice *currentSlice;
    Macroblock *mb_data;
    SyntaxElement MB_SyntaxElements[1200];
    int *quad;
    int *intra_block;
    int tr;
    int fld_type;
    unsigned int fld_flag;
    unsigned int rd_pass;
    int direct_intraP_ref[4][4];
    int pstruct_next_P;
    int imgtr_next_P_frm;
    int imgtr_last_P_frm;
    int imgtr_next_P_fld;
    int imgtr_last_P_fld;
    double b_interval;
    int p_interval;
    int b_frame_to_code;
    int fw_mb_mode;
    int bw_mb_mode;
    short ******pred_mv;
    short ******all_mv;
    short ******bipred_mv1;
    short ******bipred_mv2;
    short bi_pred_me[15];
    int LFDisableIdc;
    int LFAlphaC0Offset;
    int LFBetaOffset;
    int direct_spatial_mv_pred_flag;
    int num_ref_idx_l0_active;
    int num_ref_idx_l1_active;
    int field_mode;
    int top_field;
    int mvscale[6][32];
    int buf_cycle;
    int i16offset;
    int layer;
    int old_layer;
    int NoResidueDirect;
    int AdaptiveRounding;
    int redundant_pic_cnt;
    int MbaffFrameFlag;
    unsigned int pic_order_cnt_type;
    unsigned int delta_pic_order_always_zero_flag;
    int offset_for_non_ref_pic;
    int offset_for_top_to_bottom_field;
    unsigned int num_ref_frames_in_pic_order_cnt_cycle;
    int offset_for_ref_frame[1];
    unsigned int pic_order_cnt_lsb;
    int delta_pic_order_cnt_bottom;
    int delta_pic_order_cnt[2];
    unsigned int field_picture;
    signed int toppoc;
    signed int bottompoc;
    signed int framepoc;
    signed int ThisPOC;
    unsigned int frame_num;
    unsigned int PicWidthInMbs;
    unsigned int PicHeightInMapUnits;
    unsigned int FrameHeightInMbs;
    unsigned int PicHeightInMbs;
    unsigned int PicSizeInMbs;
    unsigned int FrameSizeInMbs;
    unsigned int pic_order_present_flag;
    int nal_reference_idc;
    int adaptive_ref_pic_buffering_flag;
    int no_output_of_prior_pics_flag;
    int long_term_reference_flag;
    DecRefPicMarking_t *dec_ref_pic_marking_buffer;
    int model_number;
    int NumberofHeaderBits;
    int NumberofTextureBits;
    int NumberofBasicUnitHeaderBits;
    int NumberofBasicUnitTextureBits;
    double TotalMADBasicUnit;
    int NumberofMBTextureBits;
    int NumberofMBHeaderBits;
    int NumberofCodedBFrame;
    int NumberofCodedPFrame;
    int NumberofGOP;
    int TotalQpforPPicture;
    int NumberofPPicture;
    double *MADofMB;
    int BasicUnitQP;
    int TopFieldFlag;
    int FieldControl;
    int FieldFrame;
    int Frame_Total_Number_MB;
    int IFLAG;
    int NumberofCodedMacroBlocks;
    int BasicUnit;
    int write_macroblock;
    int bot_MB;
    int write_macroblock_frame;
    int DeblockCall;
    int last_pic_bottom_field;
    int last_has_mmco_5;
    int pre_frame_num;
    int slice_group_change_cycle;
    int pic_unit_size_on_disk;
    int bitdepth_luma;
    int bitdepth_chroma;
    int bitdepth_luma_qp_scale;
    int bitdepth_chroma_qp_scale;
    int bitdepth_lambda_scale;
    double **lambda_md;
    double **lambda_me;
    int **lambda_mf;
    unsigned int dc_pred_value;
    int max_imgpel_value;
    int max_imgpel_value_uv;
    int num_blk8x8_uv;
    int num_cdc_coeff;
    int yuv_format;
    int lossless_qpprime_flag;
    int mb_cr_size_x;
    int mb_cr_size_y;
    int chroma_qp_offset[2];
    int residue_transform_flag;
    int auto_crop_right;
    int auto_crop_bottom;
    short checkref;
    int last_valid_reference;
    int bytes_in_picture;
} ImageParameters;
extern ImageParameters * restrict img;
extern int  b[8] ;
extern int  m6[8][8] ;

void loop()
{
#pragma scop

    for(i = 0; i < 8; i++)
    {
        a[0] = img -> m7[i][0] + img -> m7[i][7];
        a[1] = img -> m7[i][1] + img -> m7[i][6];
        a[2] = img -> m7[i][2] + img -> m7[i][5];
        a[3] = img -> m7[i][3] + img -> m7[i][4];
        b[0] = a[0] + a[3];
        b[1] = a[1] + a[2];
        b[2] = a[0] - a[3];
        b[3] = a[1] - a[2];
        a[4] = img -> m7[i][0] - img -> m7[i][7];
        a[5] = img -> m7[i][1] - img -> m7[i][6];
        a[6] = img -> m7[i][2] - img -> m7[i][5];
        a[7] = img -> m7[i][3] - img -> m7[i][4];
        b[4] = a[5] + a[6] +((a[4] >> 1) + a[4]);
        b[5] = a[4] - a[7] -((a[6] >> 1) + a[6]);
        b[6] = a[4] + a[7] -((a[5] >> 1) + a[5]);
        b[7] = a[5] - a[6] +((a[7] >> 1) + a[7]);
        m6[0][i] = b[0] + b[1];
        m6[2][i] = b[2] +(b[3] >> 1);
        m6[4][i] = b[0] - b[1];
        m6[6][i] =(b[2] >> 1) - b[3];
        m6[1][i] = b[4] +(b[7] >> 2);
        m6[3][i] = b[5] +(b[6] >> 2);
        m6[5][i] = b[6] -(b[5] >> 2);
        m6[7][i] = -b[7] +(b[4] >> 2);
    }

#pragma endscop
}
