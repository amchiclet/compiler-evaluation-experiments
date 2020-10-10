#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int i;
enum FRAME_enum {FRAME=0,TOP_FIELD=1,BOTTOM_FIELD=2};;
typedef enum FRAME_enum PictureStructure;
typedef unsigned char byte;
typedef long long int64;
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
struct storable_picture
{
    PictureStructure structure;
    int poc;
    int top_poc;
    int bottom_poc;
    int frame_poc;
    int64 ref_pic_num[50][6][33];
    int64 frm_ref_pic_num[50][6][33];
    int64 top_ref_pic_num[50][6][33];
    int64 bottom_ref_pic_num[50][6][33];
    unsigned int frame_num;
    int pic_num;
    int long_term_pic_num;
    int long_term_frame_idx;
    int is_long_term;
    int used_for_reference;
    int is_output;
    int non_existing;
    short max_slice_id;
    int size_x;
    int size_y;
    int size_x_cr;
    int size_y_cr;
    int chroma_vector_adjustment;
    int coded_frame;
    int MbaffFrameFlag;
    unsigned int PicWidthInMbs;
    unsigned int PicSizeInMbs;
    unsigned short **imgY;
    unsigned short ***imgUV;
    byte *mb_field;
    short **slice_id;
    char ***ref_idx;
    int64 ***ref_pic_id;
    int64 ***ref_id;
    short ****mv;
    byte **moving_block;
    byte **field_frame;
    struct storable_picture *top_field;
    struct storable_picture *bottom_field;
    struct storable_picture *frame;
    int slice_type;
    int idr_flag;
    int no_output_of_prior_pics_flag;
    int long_term_reference_flag;
    int adaptive_ref_pic_buffering_flag;
    int chroma_format_idc;
    int frame_mbs_only_flag;
    int frame_cropping_flag;
    int frame_cropping_rect_left_offset;
    int frame_cropping_rect_right_offset;
    int frame_cropping_rect_top_offset;
    int frame_cropping_rect_bottom_offset;
    int qp;
    int chroma_qp_offset[2];
    int slice_qp_delta;
    DecRefPicMarking_t *dec_ref_pic_marking_buffer;
    int concealed_pic;
};

typedef struct storable_picture  StorablePicture;
extern StorablePicture * restrict dec_picture;
enum LIST_0_enum {LIST_0=0,LIST_1=1};;
typedef struct
{
    int read_len;
    int code_len;
    int frame_bitoffset;
    int bitstream_length;
    byte *streamBuffer;
    int ei_flag;
} Bitstream;
typedef struct
{
    unsigned int Dlow;
    unsigned int Drange;
    unsigned int Dvalue;
    unsigned int Dbuffer;
    int Dbits_to_go;
    byte *Dcodestrm;
    int *Dcodestrm_len;
} DecodingEnvironment;
struct datapartition
{
    Bitstream *bitstream;
    DecodingEnvironment de_cabac;
};

typedef struct datapartition  DataPartition;
typedef struct
{
    unsigned short state;
    unsigned char MPS;
} BiContextType;
typedef struct
{
    BiContextType mb_type_contexts[4][11];
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
typedef struct
{
    int ei_flag;
    int qp;
    int slice_qp_delta;
    int picture_type;
    PictureStructure structure;
    int start_mb_nr;
    int max_part_nr;
    int dp_mode;
    int next_header;
    DataPartition *partArr;
    MotionInfoContexts *mot_ctx;
    TextureInfoContexts *tex_ctx;
    int ref_pic_list_reordering_flag_l0;
    int *reordering_of_pic_nums_idc_l0;
    int *abs_diff_pic_num_minus1_l0;
    int *long_term_pic_idx_l0;
    int ref_pic_list_reordering_flag_l1;
    int *reordering_of_pic_nums_idc_l1;
    int *abs_diff_pic_num_minus1_l1;
    int *long_term_pic_idx_l1;
    int LFDisableIdc;
    int LFAlphaC0Offset;
    int LFBetaOffset;
    int pic_parameter_set_id;
} Slice;
struct macroblock
{
    int qp;
    int slice_nr;
    int delta_quant;
    struct macroblock *mb_available_up;
    struct macroblock *mb_available_left;
    int mb_type;
    int mvd[2][16 / 4][16 / 4][2];
    int cbp;
    int64 cbp_blk;
    int64 cbp_bits;
    int is_skip;
    int i16mode;
    int b8mode[4];
    int b8pdir[4];
    int ei_flag;
    int LFDisableIdc;
    int LFAlphaC0Offset;
    int LFBetaOffset;
    int c_ipred_mode;
    int mb_field;
    int skip_flag;
    int mbAddrA;
    int mbAddrB;
    int mbAddrC;
    int mbAddrD;
    int mbAvailA;
    int mbAvailB;
    int mbAvailC;
    int mbAvailD;
    int luma_transform_size_8x8_flag;
    int NoMbPartLessThan8x8Flag;
};

typedef struct macroblock  Macroblock;
typedef long __time_t;
typedef __time_t time_t;
struct timeb
{
    time_t time;
    unsigned short millitm;
    short timezone;
    short dstflag;
};

struct img_par
{
    int number;
    unsigned int current_mb_nr;
    unsigned int num_dec_mb;
    int current_slice_nr;
    int *intra_block;
    int tr;
    int qp;
    int qpsp;
    int sp_switch;
    int direct_spatial_mv_pred_flag;
    int type;
    int width;
    int height;
    int width_cr;
    int height_cr;
    int mb_y;
    int mb_x;
    int block_y;
    int pix_y;
    int pix_x;
    int pix_c_y;
    int block_x;
    int pix_c_x;
    int allrefzero;
    unsigned short mpr[16][16];
    int mvscale[6][32];
    int m7[16][16];
    int cof[4][12][4][4];
    int cofu[16];
    int **ipredmode;
    int *quad;
    int ***nz_coeff;
    int **siblock;
    int cod_counter;
    int newframe;
    int structure;
    int pstruct_next_P;
    Slice *currentSlice;
    Macroblock *mb_data;
    int subblock_x;
    int subblock_y;
    int is_intra_block;
    int is_v_block;
    int MbaffFrameFlag;
    int DeblockCall;
    int **field_anchor;
    DecRefPicMarking_t *dec_ref_pic_marking_buffer;
    int disposable_flag;
    int num_ref_idx_l0_active;
    int num_ref_idx_l1_active;
    int slice_group_change_cycle;
    int redundant_slice_flag;
    int redundant_pic_cnt;
    int explicit_B_prediction;
    unsigned int pre_frame_num;
    int toppoc;
    int bottompoc;
    int framepoc;
    unsigned int frame_num;
    unsigned int field_pic_flag;
    unsigned int bottom_field_flag;
    unsigned int pic_order_cnt_lsb;
    int delta_pic_order_cnt_bottom;
    int delta_pic_order_cnt[3];
    signed int PrevPicOrderCntMsb;
    unsigned int PrevPicOrderCntLsb;
    signed int PicOrderCntMsb;
    unsigned int AbsFrameNum;
    signed int ExpectedPicOrderCnt;
    signed int PicOrderCntCycleCnt;
    signed int FrameNumInPicOrderCntCycle;
    unsigned int PreviousFrameNum;
    unsigned int FrameNumOffset;
    int ExpectedDeltaPerPicOrderCntCycle;
    int PreviousPOC;
    int ThisPOC;
    int PreviousFrameNumOffset;
    unsigned int luma_log2_weight_denom;
    unsigned int chroma_log2_weight_denom;
    int ***wp_weight;
    int ***wp_offset;
    int ****wbp_weight;
    int wp_round_luma;
    int wp_round_chroma;
    unsigned int apply_weights;
    int idr_flag;
    int nal_reference_idc;
    int idr_pic_id;
    int MaxFrameNum;
    unsigned int PicWidthInMbs;
    unsigned int PicHeightInMapUnits;
    unsigned int FrameHeightInMbs;
    unsigned int PicHeightInMbs;
    unsigned int PicSizeInMbs;
    unsigned int FrameSizeInMbs;
    unsigned int oldFrameSizeInMbs;
    int no_output_of_prior_pics_flag;
    int long_term_reference_flag;
    int adaptive_ref_pic_buffering_flag;
    int last_has_mmco_5;
    int last_pic_bottom_field;
    int model_number;
    int pic_unit_bitsize_on_disk;
    int bitdepth_luma;
    int bitdepth_chroma;
    int bitdepth_luma_qp_scale;
    int bitdepth_chroma_qp_scale;
    unsigned int dc_pred_value;
    int max_imgpel_value;
    int max_imgpel_value_uv;
    int Transform8x8Mode;
    int profile_idc;
    int yuv_format;
    int lossless_qpprime_flag;
    int num_blk8x8_uv;
    int num_cdc_coeff;
    int mb_cr_size_x;
    int mb_cr_size_y;
    int idr_psnr_number;
    int psnr_number;
    time_t ltime_start;
    time_t ltime_end;
    int residue_transform_flag;
    struct timeb tstruct_start;
    struct timeb tstruct_end;
    int last_ref_pic_poc;
    int ref_poc_gap;
    int poc_gap;
    int conceal_mode;
    int earlier_missing_poc;
    unsigned int frame_to_conceal;
    int IDR_concealment_flag;
    int conceal_slice_type;
};

extern struct img_par * restrict img;

void loop()
{
#pragma scop

    for(j = 0; j < 4; j++) for(i = 0; i < 4; i++)
        {
            dec_picture -> ref_idx[LIST_0][img -> block_y + j][img -> block_x + i] =(- 1);
            dec_picture -> ref_idx[LIST_1][img -> block_y + j][img -> block_x + i] =(- 1);
            dec_picture -> ref_pic_id[LIST_0][img -> block_y + j][img -> block_x + i] = - 9223372036854775807LL - 1LL;
            dec_picture -> ref_pic_id[LIST_1][img -> block_y + j][img -> block_x + i] = - 9223372036854775807LL - 1LL;
        }

#pragma endscop
}
