#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
enum AVOptionType {FF_OPT_TYPE_FLAGS=0,FF_OPT_TYPE_INT=1,FF_OPT_TYPE_INT64=2,FF_OPT_TYPE_DOUBLE=3,FF_OPT_TYPE_FLOAT=4,FF_OPT_TYPE_STRING=5,FF_OPT_TYPE_RATIONAL=6,FF_OPT_TYPE_CONST=128};;
struct AVOption
{
    const char *name;
    const char *help;
    int offset;
    enum AVOptionType type;
    double default_val;
    double min;
    double max;
    int flags;
    const char *unit;
};

struct AVCLASS
{
    const char *class_name;
    struct AVOption *option;
};

typedef struct AVCLASS AVClass;
struct AVRational
{
    int num;
    int den;
};

typedef struct AVRational  AVRational;
enum PixelFormat {PIX_FMT_NONE=-1,PIX_FMT_YUV420P=0,PIX_FMT_YUV422=1,PIX_FMT_RGB24=2,PIX_FMT_BGR24=3,PIX_FMT_YUV422P=4,PIX_FMT_YUV444P=5,PIX_FMT_RGBA32=6,PIX_FMT_YUV410P=7,PIX_FMT_YUV411P=8,PIX_FMT_RGB565=9,PIX_FMT_RGB555=10,PIX_FMT_GRAY8=11,PIX_FMT_MONOWHITE=12,PIX_FMT_MONOBLACK=13,PIX_FMT_PAL8=14,PIX_FMT_YUVJ420P=15,PIX_FMT_YUVJ422P=16,PIX_FMT_YUVJ444P=17,PIX_FMT_XVMC_MPEG2_MC=18,PIX_FMT_XVMC_MPEG2_IDCT=19,PIX_FMT_UYVY422=20,PIX_FMT_UYVY411=21,PIX_FMT_NB=22};;
enum SampleFormat {SAMPLE_FMT_NONE=-1,SAMPLE_FMT_U8=0,SAMPLE_FMT_S16=1,SAMPLE_FMT_S24=2,SAMPLE_FMT_S32=3,SAMPLE_FMT_FLT=4};;
enum CodecType {CODEC_TYPE_UNKNOWN=-1,CODEC_TYPE_VIDEO=0,CODEC_TYPE_AUDIO=1,CODEC_TYPE_DATA=2,CODEC_TYPE_SUBTITLE=3};;
enum CodecID {CODEC_ID_NONE=0,CODEC_ID_MPEG1VIDEO=1,CODEC_ID_MPEG2VIDEO=2,CODEC_ID_MPEG2VIDEO_XVMC=3,CODEC_ID_H261=4,CODEC_ID_H263=5,CODEC_ID_RV10=6,CODEC_ID_RV20=7,CODEC_ID_MJPEG=8,CODEC_ID_MJPEGB=9,CODEC_ID_LJPEG=10,CODEC_ID_SP5X=11,CODEC_ID_JPEGLS=12,CODEC_ID_MPEG4=13,CODEC_ID_RAWVIDEO=14,CODEC_ID_MSMPEG4V1=15,CODEC_ID_MSMPEG4V2=16,CODEC_ID_MSMPEG4V3=17,CODEC_ID_WMV1=18,CODEC_ID_WMV2=19,CODEC_ID_H263P=20,CODEC_ID_H263I=21,CODEC_ID_FLV1=22,CODEC_ID_SVQ1=23,CODEC_ID_SVQ3=24,CODEC_ID_DVVIDEO=25,CODEC_ID_HUFFYUV=26,CODEC_ID_CYUV=27,CODEC_ID_H264=28,CODEC_ID_INDEO3=29,CODEC_ID_VP3=30,CODEC_ID_THEORA=31,CODEC_ID_ASV1=32,CODEC_ID_ASV2=33,CODEC_ID_FFV1=34,CODEC_ID_4XM=35,CODEC_ID_VCR1=36,CODEC_ID_CLJR=37,CODEC_ID_MDEC=38,CODEC_ID_ROQ=39,CODEC_ID_INTERPLAY_VIDEO=40,CODEC_ID_XAN_WC3=41,CODEC_ID_XAN_WC4=42,CODEC_ID_RPZA=43,CODEC_ID_CINEPAK=44,CODEC_ID_WS_VQA=45,CODEC_ID_MSRLE=46,CODEC_ID_MSVIDEO1=47,CODEC_ID_IDCIN=48,CODEC_ID_8BPS=49,CODEC_ID_SMC=50,CODEC_ID_FLIC=51,CODEC_ID_TRUEMOTION1=52,CODEC_ID_VMDVIDEO=53,CODEC_ID_MSZH=54,CODEC_ID_ZLIB=55,CODEC_ID_QTRLE=56,CODEC_ID_SNOW=57,CODEC_ID_TSCC=58,CODEC_ID_ULTI=59,CODEC_ID_QDRAW=60,CODEC_ID_VIXL=61,CODEC_ID_QPEG=62,CODEC_ID_XVID=63,CODEC_ID_PNG=64,CODEC_ID_PPM=65,CODEC_ID_PBM=66,CODEC_ID_PGM=67,CODEC_ID_PGMYUV=68,CODEC_ID_PAM=69,CODEC_ID_FFVHUFF=70,CODEC_ID_RV30=71,CODEC_ID_RV40=72,CODEC_ID_VC9=73,CODEC_ID_WMV3=74,CODEC_ID_LOCO=75,CODEC_ID_WNV1=76,CODEC_ID_AASC=77,CODEC_ID_INDEO2=78,CODEC_ID_FRAPS=79,CODEC_ID_TRUEMOTION2=80,CODEC_ID_BMP=81,CODEC_ID_CSCD=82,CODEC_ID_MMVIDEO=83,CODEC_ID_ZMBV=84,CODEC_ID_AVS=85,CODEC_ID_SMACKVIDEO=86,CODEC_ID_NUV=87,CODEC_ID_KMVC=88,CODEC_ID_PCM_S16LE=65536,CODEC_ID_PCM_S16BE=65537,CODEC_ID_PCM_U16LE=65538,CODEC_ID_PCM_U16BE=65539,CODEC_ID_PCM_S8=65540,CODEC_ID_PCM_U8=65541,CODEC_ID_PCM_MULAW=65542,CODEC_ID_PCM_ALAW=65543,CODEC_ID_PCM_S32LE=65544,CODEC_ID_PCM_S32BE=65545,CODEC_ID_PCM_U32LE=65546,CODEC_ID_PCM_U32BE=65547,CODEC_ID_PCM_S24LE=65548,CODEC_ID_PCM_S24BE=65549,CODEC_ID_PCM_U24LE=65550,CODEC_ID_PCM_U24BE=65551,CODEC_ID_PCM_S24DAUD=65552,CODEC_ID_ADPCM_IMA_QT=69632,CODEC_ID_ADPCM_IMA_WAV=69633,CODEC_ID_ADPCM_IMA_DK3=69634,CODEC_ID_ADPCM_IMA_DK4=69635,CODEC_ID_ADPCM_IMA_WS=69636,CODEC_ID_ADPCM_IMA_SMJPEG=69637,CODEC_ID_ADPCM_MS=69638,CODEC_ID_ADPCM_4XM=69639,CODEC_ID_ADPCM_XA=69640,CODEC_ID_ADPCM_ADX=69641,CODEC_ID_ADPCM_EA=69642,CODEC_ID_ADPCM_G726=69643,CODEC_ID_ADPCM_CT=69644,CODEC_ID_ADPCM_SWF=69645,CODEC_ID_ADPCM_YAMAHA=69646,CODEC_ID_ADPCM_SBPRO_4=69647,CODEC_ID_ADPCM_SBPRO_3=69648,CODEC_ID_ADPCM_SBPRO_2=69649,CODEC_ID_AMR_NB=73728,CODEC_ID_AMR_WB=73729,CODEC_ID_RA_144=77824,CODEC_ID_RA_288=77825,CODEC_ID_ROQ_DPCM=81920,CODEC_ID_INTERPLAY_DPCM=81921,CODEC_ID_XAN_DPCM=81922,CODEC_ID_SOL_DPCM=81923,CODEC_ID_MP2=86016,CODEC_ID_MP3=86017,CODEC_ID_AAC=86018,CODEC_ID_MPEG4AAC=86019,CODEC_ID_AC3=86020,CODEC_ID_DTS=86021,CODEC_ID_VORBIS=86022,CODEC_ID_DVAUDIO=86023,CODEC_ID_WMAV1=86024,CODEC_ID_WMAV2=86025,CODEC_ID_MACE3=86026,CODEC_ID_MACE6=86027,CODEC_ID_VMDAUDIO=86028,CODEC_ID_SONIC=86029,CODEC_ID_SONIC_LS=86030,CODEC_ID_FLAC=86031,CODEC_ID_MP3ADU=86032,CODEC_ID_MP3ON4=86033,CODEC_ID_SHORTEN=86034,CODEC_ID_ALAC=86035,CODEC_ID_WESTWOOD_SND1=86036,CODEC_ID_GSM=86037,CODEC_ID_QDM2=86038,CODEC_ID_COOK=86039,CODEC_ID_TRUESPEECH=86040,CODEC_ID_TTA=86041,CODEC_ID_SMACKAUDIO=86042,CODEC_ID_OGGTHEORA=90112,CODEC_ID_DVD_SUBTITLE=94208,CODEC_ID_DVB_SUBTITLE=94209,CODEC_ID_MPEG2TS=131072};;
struct AVCodec
{
    const char *name;
    enum CodecType type;
    enum CodecID id;
    int priv_data_size;
    int capabilities;
    struct AVCodec *next;
    const AVRational *supported_framerates;
    const enum PixelFormat *pix_fmts;
};

struct RcOverride
{
    int start_frame;
    int end_frame;
    int qscale;
    float quality_factor;
};

typedef struct RcOverride  RcOverride;
typedef unsigned char uint8_t;
typedef long int64_t;
typedef signed char int8_t;
typedef unsigned int uint32_t;
typedef unsigned long uint64_t;
struct AVPanScan
{
    int id;
    int width;
    int height;
    int16_t position[3][2];
};

typedef struct AVPanScan  AVPanScan;
struct AVFrame
{
    uint8_t *data[4];
    int linesize[4];
    uint8_t *base[4];
    int key_frame;
    int pict_type;
    int64_t pts;
    int coded_picture_number;
    int display_picture_number;
    int quality;
    int age;
    int reference;
    int8_t *qscale_table;
    int qstride;
    uint8_t *mbskip_table;
    int16_t(*motion_val[2])[2];
    uint32_t *mb_type;
    uint8_t motion_subsample_log2;
    void *opaque;
    uint64_t error[4];
    int type;
    int repeat_pict;
    int qscale_type;
    int interlaced_frame;
    int top_field_first;
    AVPanScan *pan_scan;
    int palette_has_changed;
    int buffer_hints;
    short *dct_coeff;
    int8_t *ref_index[2];
};

typedef struct AVFrame  AVFrame;
typedef unsigned short uint16_t;
struct AVPaletteControl
{
    int palette_changed;
    unsigned int palette[256];
};

enum AVDiscard {AVDISCARD_NONE=-16,AVDISCARD_DEFAULT=0,AVDISCARD_NONREF=8,AVDISCARD_BIDIR=16,AVDISCARD_NONKEY=32,AVDISCARD_ALL=48};;
struct AVCodecContext
{
    AVClass *av_class;
    int bit_rate;
    int bit_rate_tolerance;
    int flags;
    int sub_id;
    int me_method;
    void *extradata;
    int extradata_size;
    AVRational time_base;
    int width;
    int height;
    int gop_size;
    enum PixelFormat pix_fmt;
    int rate_emu;
    int sample_rate;
    int channels;
    enum SampleFormat sample_fmt;
    int frame_size;
    int frame_number;
    int real_pict_num;
    int delay;
    float qcompress;
    float qblur;
    int qmin;
    int qmax;
    int max_qdiff;
    int max_b_frames;
    float b_quant_factor;
    int rc_strategy;
    int b_frame_strategy;
    int hurry_up;
    struct AVCodec *codec;
    void *priv_data;
    int rtp_mode;
    int rtp_payload_size;
    int mv_bits;
    int header_bits;
    int i_tex_bits;
    int p_tex_bits;
    int i_count;
    int p_count;
    int skip_count;
    int misc_bits;
    int frame_bits;
    void *opaque;
    char codec_name[32];
    enum CodecType codec_type;
    enum CodecID codec_id;
    unsigned int codec_tag;
    int workaround_bugs;
    int luma_elim_threshold;
    int chroma_elim_threshold;
    int strict_std_compliance;
    float b_quant_offset;
    int error_resilience;
    int has_b_frames;
    int block_align;
    int parse_only;
    int mpeg_quant;
    char *stats_out;
    char *stats_in;
    float rc_qsquish;
    float rc_qmod_amp;
    int rc_qmod_freq;
    RcOverride *rc_override;
    int rc_override_count;
    char *rc_eq;
    int rc_max_rate;
    int rc_min_rate;
    int rc_buffer_size;
    float rc_buffer_aggressivity;
    float i_quant_factor;
    float i_quant_offset;
    float rc_initial_cplx;
    int dct_algo;
    float lumi_masking;
    float temporal_cplx_masking;
    float spatial_cplx_masking;
    float p_masking;
    float dark_masking;
    int unused;
    int idct_algo;
    int slice_count;
    int *slice_offset;
    int error_concealment;
    unsigned int dsp_mask;
    int bits_per_sample;
    int prediction_method;
    AVRational sample_aspect_ratio;
    AVFrame *coded_frame;
    int debug;
    int debug_mv;
    uint64_t error[4];
    int mb_qmin;
    int mb_qmax;
    int me_cmp;
    int me_sub_cmp;
    int mb_cmp;
    int ildct_cmp;
    int dia_size;
    int last_predictor_count;
    int pre_me;
    int me_pre_cmp;
    int pre_dia_size;
    int me_subpel_quality;
    int dtg_active_format;
    int me_range;
    int intra_quant_bias;
    int inter_quant_bias;
    int color_table_id;
    int internal_buffer_count;
    void *internal_buffer;
    int global_quality;
    int coder_type;
    int context_model;
    int slice_flags;
    int xvmc_acceleration;
    int mb_decision;
    uint16_t *intra_matrix;
    uint16_t *inter_matrix;
    unsigned int stream_codec_tag;
    int scenechange_threshold;
    int lmin;
    int lmax;
    struct AVPaletteControl *palctrl;
    int noise_reduction;
    int rc_initial_buffer_occupancy;
    int inter_threshold;
    int flags2;
    int error_rate;
    int antialias_algo;
    int quantizer_noise_shaping;
    int thread_count;
    void *thread_opaque;
    int me_threshold;
    int mb_threshold;
    int intra_dc_precision;
    int nsse_weight;
    int skip_top;
    int skip_bottom;
    int profile;
    int level;
    int lowres;
    int coded_width;
    int coded_height;
    int frame_skip_threshold;
    int frame_skip_factor;
    int frame_skip_exp;
    int frame_skip_cmp;
    float border_masking;
    int mb_lmin;
    int mb_lmax;
    int me_penalty_compensation;
    enum AVDiscard skip_loop_filter;
    enum AVDiscard skip_idct;
    enum AVDiscard skip_frame;
    int bidir_refine;
    int brd_scale;
    int crf;
    int cqp;
    int keyint_min;
    int refs;
    int chromaoffset;
    int bframebias;
    int trellis;
    float complexityblur;
    int deblockalpha;
    int deblockbeta;
    int partitions;
    int directpred;
    int cutoff;
    int scenechange_factor;
};

enum OutputFormat {FMT_MPEG1=0,FMT_H261=1,FMT_H263=2,FMT_MJPEG=3,FMT_H264=4};;
struct PutBitContext
{
    uint32_t bit_buf;
    int bit_left;
    uint8_t *buf;
    uint8_t *buf_ptr;
    uint8_t *buf_end;
};

typedef struct PutBitContext  PutBitContext;
typedef int int32_t;
struct Picture
{
    uint8_t *data[4];
    int linesize[4];
    uint8_t *base[4];
    int key_frame;
    int pict_type;
    int64_t pts;
    int coded_picture_number;
    int display_picture_number;
    int quality;
    int age;
    int reference;
    int8_t *qscale_table;
    int qstride;
    uint8_t *mbskip_table;
    int16_t(*motion_val[2])[2];
    uint32_t *mb_type;
    uint8_t motion_subsample_log2;
    void *opaque;
    uint64_t error[4];
    int type;
    int repeat_pict;
    int qscale_type;
    int interlaced_frame;
    int top_field_first;
    AVPanScan *pan_scan;
    int palette_has_changed;
    int buffer_hints;
    short *dct_coeff;
    int8_t *ref_index[2];
    uint8_t *interpolated[3];
    int16_t(*motion_val_base[2])[2];
    uint32_t *mb_type_base;
    int field_poc[2];
    int poc;
    int frame_num;
    int pic_id;
    int long_ref;
    int ref_poc[2][16];
    int ref_count[2];
    int mb_var_sum;
    int mc_mb_var_sum;
    uint16_t *mb_var;
    uint16_t *mc_mb_var;
    uint8_t *mb_mean;
    int32_t *mb_cmp_score;
    int b_frame_score;
};

typedef struct Picture  Picture;
typedef short int16_t;
struct DSPContext
{
    uint8_t idct_permutation[64];
    int idct_permutation_type;
};

typedef struct DSPContext  DSPContext;
typedef struct AVCodecContext  AVCodecContext;
struct MotionEstContext
{
    AVCodecContext *avctx;
    int skip;
    int co_located_mv[4][2];
    int direct_basis_mv[4][2];
    uint8_t *scratchpad;
    uint8_t *best_mb;
    uint8_t *temp_mb[2];
    uint8_t *temp;
    int best_bits;
    uint32_t *map;
    uint32_t *score_map;
    int map_generation;
    int pre_penalty_factor;
    int penalty_factor;
    int sub_penalty_factor;
    int mb_penalty_factor;
    int flags;
    int sub_flags;
    int mb_flags;
    int pre_pass;
    int dia_size;
    int xmin;
    int xmax;
    int ymin;
    int ymax;
    int pred_x;
    int pred_y;
    uint8_t *src[4][4];
    uint8_t *ref[4][4];
    int stride;
    int uvstride;
    int mc_mb_var_sum_temp;
    int mb_var_sum_temp;
    int scene_change_score;
    uint8_t(*mv_penalty)[2048 * 2 + 1];
    uint8_t *current_mv_penalty;
};

typedef struct MotionEstContext  MotionEstContext;
struct ScanTable
{
    const uint8_t *scantable;
    uint8_t permutated[64];
    uint8_t raster_end[64];
};

typedef struct ScanTable  ScanTable;
struct RateControlEntry
{
    int pict_type;
    float qscale;
    int mv_bits;
    int i_tex_bits;
    int p_tex_bits;
    int misc_bits;
    int header_bits;
    uint64_t expected_bits;
    int new_pict_type;
    float new_qscale;
    int mc_mb_var_sum;
    int mb_var_sum;
    int i_count;
    int skip_count;
    int f_code;
    int b_code;
};

typedef struct RateControlEntry  RateControlEntry;
struct Predictor
{
    double coeff;
    double count;
    double decay;
};

typedef struct Predictor  Predictor;
struct RateControlContext
{
    FILE *stats_file;
    int num_entries;
    RateControlEntry *entry;
    double buffer_index;
    Predictor pred[5];
    double short_term_qsum;
    double short_term_qcount;
    double pass1_rc_eq_output_sum;
    double pass1_wanted_bits;
    double last_qscale;
    double last_qscale_for[5];
    int last_mc_mb_var_sum;
    int last_mb_var_sum;
    uint64_t i_cplx_sum[5];
    uint64_t p_cplx_sum[5];
    uint64_t mv_bits_sum[5];
    uint64_t qscale_sum[5];
    int frame_count[5];
    int last_non_b_pict_type;
    void *non_lavc_opaque;
    float dry_run_qscale;
    int last_picture_number;
};

typedef struct RateControlContext  RateControlContext;
struct GetBitContext
{
    const uint8_t *buffer;
    const uint8_t *buffer_end;
    int index;
    int size_in_bits;
};

typedef struct GetBitContext  GetBitContext;
struct ParseContext
{
    uint8_t *buffer;
    int index;
    int last_index;
    unsigned int buffer_size;
    uint32_t state;
    int frame_start_found;
    int overread;
    int overread_index;
};

typedef struct ParseContext  ParseContext;
struct MJpegContext
{
    uint8_t huff_size_dc_luminance[12];
    uint16_t huff_code_dc_luminance[12];
    uint8_t huff_size_dc_chrominance[12];
    uint16_t huff_code_dc_chrominance[12];
    uint8_t huff_size_ac_luminance[256];
    uint16_t huff_code_ac_luminance[256];
    uint8_t huff_size_ac_chrominance[256];
    uint16_t huff_code_ac_chrominance[256];
};

struct MpegEncContext
{
    struct AVCodecContext *avctx;
    int width;
    int height;
    int gop_size;
    int intra_only;
    int bit_rate;
    enum OutputFormat out_format;
    int h263_pred;
    int h263_plus;
    int h263_msmpeg4;
    int h263_flv;
    enum CodecID codec_id;
    int fixed_qscale;
    int encoding;
    int flags;
    int flags2;
    int max_b_frames;
    int luma_elim_threshold;
    int chroma_elim_threshold;
    int strict_std_compliance;
    int workaround_bugs;
    PutBitContext pb;
    int context_initialized;
    int input_picture_number;
    int coded_picture_number;
    int picture_number;
    int picture_in_gop_number;
    int b_frames_since_non_b;
    int64_t user_specified_pts;
    int mb_width;
    int mb_height;
    int mb_stride;
    int b8_stride;
    int b4_stride;
    int h_edge_pos;
    int v_edge_pos;
    int mb_num;
    int linesize;
    int uvlinesize;
    Picture *picture;
    Picture **input_picture;
    Picture **reordered_input_picture;
    int start_mb_y;
    int end_mb_y;
    struct MpegEncContext *thread_context[8];
    Picture last_picture;
    Picture next_picture;
    Picture new_picture;
    Picture current_picture;
    Picture *last_picture_ptr;
    Picture *next_picture_ptr;
    Picture *current_picture_ptr;
    uint8_t *visualization_buffer[3];
    int last_dc[3];
    int16_t *dc_val_base;
    int16_t *dc_val[3];
    int16_t dc_cache[4 * 5];
    int y_dc_scale;
    int c_dc_scale;
    const uint8_t *y_dc_scale_table;
    const uint8_t *c_dc_scale_table;
    const uint8_t *chroma_qscale_table;
    uint8_t *coded_block_base;
    uint8_t *coded_block;
    int16_t(*ac_val_base)[16];
    int16_t(*ac_val[3])[16];
    int ac_pred;
    uint8_t *prev_pict_types;
    int mb_skipped;
    uint8_t *mbskip_table;
    uint8_t *mbintra_table;
    uint8_t *cbp_table;
    uint8_t *pred_dir_table;
    uint8_t *allocated_edge_emu_buffer;
    uint8_t *edge_emu_buffer;
    uint8_t *rd_scratchpad;
    uint8_t *obmc_scratchpad;
    uint8_t *b_scratchpad;
    int qscale;
    int chroma_qscale;
    int lambda;
    int lambda2;
    int *lambda_table;
    int adaptive_quant;
    int dquant;
    int pict_type;
    int last_pict_type;
    int last_non_b_pict_type;
    int dropable;
    int frame_rate_index;
    int last_lambda_for[5];
    int unrestricted_mv;
    int h263_long_vectors;
    int decode;
    DSPContext dsp;
    int f_code;
    int b_code;
    int16_t(*p_mv_table_base)[2];
    int16_t(*b_forw_mv_table_base)[2];
    int16_t(*b_back_mv_table_base)[2];
    int16_t(*b_bidir_forw_mv_table_base)[2];
    int16_t(*b_bidir_back_mv_table_base)[2];
    int16_t(*b_direct_mv_table_base)[2];
    int16_t(*p_field_mv_table_base[2][2])[2];
    int16_t(*b_field_mv_table_base[2][2][2])[2];
    int16_t(*p_mv_table)[2];
    int16_t(*b_forw_mv_table)[2];
    int16_t(*b_back_mv_table)[2];
    int16_t(*b_bidir_forw_mv_table)[2];
    int16_t(*b_bidir_back_mv_table)[2];
    int16_t(*b_direct_mv_table)[2];
    int16_t(*p_field_mv_table[2][2])[2];
    int16_t(*b_field_mv_table[2][2][2])[2];
    uint8_t *p_field_select_table[2];
    uint8_t *b_field_select_table[2][2];
    int me_method;
    int mv_dir;
    int mv_type;
    int mv[2][4][2];
    int field_select[2][2];
    int last_mv[2][2][2];
    uint8_t *fcode_tab;
    int16_t direct_scale_mv[2][64];
    MotionEstContext me;
    int no_rounding;
    int hurry_up;
    int mb_x;
    int mb_y;
    int mb_skip_run;
    int mb_intra;
    uint16_t *mb_type;
    int block_index[6];
    int block_wrap[6];
    uint8_t *dest[3];
    int *mb_index2xy;
    uint16_t intra_matrix[64];
    uint16_t chroma_intra_matrix[64];
    uint16_t inter_matrix[64];
    uint16_t chroma_inter_matrix[64];
    int intra_quant_bias;
    int inter_quant_bias;
    int min_qcoeff;
    int max_qcoeff;
    int ac_esc_length;
    uint8_t *intra_ac_vlc_length;
    uint8_t *intra_ac_vlc_last_length;
    uint8_t *inter_ac_vlc_length;
    uint8_t *inter_ac_vlc_last_length;
    uint8_t *luma_dc_vlc_length;
    uint8_t *chroma_dc_vlc_length;
    int coded_score[6];
    int(*q_intra_matrix)[64];
    int(*q_inter_matrix)[64];
    uint16_t(*q_intra_matrix16)[2][64];
    uint16_t(*q_inter_matrix16)[2][64];
    int block_last_index[12];
    ScanTable intra_scantable __attribute__((aligned(8)));
    ScanTable intra_h_scantable;
    ScanTable intra_v_scantable;
    ScanTable inter_scantable;
    int(*dct_error_sum)[64];
    int dct_count[2];
    uint16_t(*dct_offset)[64];
    void *opaque;
    int64_t wanted_bits;
    int64_t total_bits;
    int frame_bits;
    RateControlContext rc_context;
    int mv_bits;
    int header_bits;
    int i_tex_bits;
    int p_tex_bits;
    int i_count;
    int f_count;
    int b_count;
    int skip_count;
    int misc_bits;
    int last_bits;
    int error_count;
    uint8_t *error_status_table;
    int resync_mb_x;
    int resync_mb_y;
    GetBitContext last_resync_gb;
    int mb_num_left;
    int next_p_frame_damaged;
    int error_resilience;
    ParseContext parse_context;
    int gob_index;
    int obmc;
    int umvplus;
    int h263_aic;
    int h263_aic_dir;
    int h263_slice_structured;
    int alt_inter_vlc;
    int modified_quant;
    int loop_filter;
    int custom_pcf;
    int time_increment_bits;
    int last_time_base;
    int time_base;
    int64_t time_is_forbidden_due_to_security_issues;
    int64_t last_non_b_time;
    uint16_t pp_time;
    uint16_t pb_time;
    uint16_t pp_field_time;
    uint16_t pb_field_time;
    int shape;
    int vol_sprite_usage;
    int sprite_width;
    int sprite_height;
    int sprite_left;
    int sprite_top;
    int sprite_brightness_change;
    int num_sprite_warping_points;
    int real_sprite_warping_points;
    int sprite_offset[2][2];
    int sprite_delta[2][2];
    int sprite_shift[2];
    int mcsel;
    int quant_precision;
    int quarter_sample;
    int scalability;
    int hierachy_type;
    int enhancement_type;
    int new_pred;
    int reduced_res_vop;
    int aspect_ratio_info;
    int sprite_warping_accuracy;
    int low_latency_sprite;
    int data_partitioning;
    int partitioned_frame;
    int rvlc;
    int resync_marker;
    int low_delay;
    int vo_type;
    int vol_control_parameters;
    int intra_dc_threshold;
    PutBitContext tex_pb;
    PutBitContext pb2;
    int mpeg_quant;
    int t_frame;
    int padding_bug_score;
    int divx_version;
    int divx_build;
    int divx_packed;
    uint8_t *bitstream_buffer;
    int bitstream_buffer_size;
    unsigned int allocated_bitstream_buffer_size;
    int xvid_build;
    int lavc_build;
    int rv10_version;
    int rv10_first_dc_coded[3];
    struct MJpegContext *mjpeg_ctx;
    int mjpeg_vsample[3];
    int mjpeg_hsample[3];
    int mjpeg_write_tables;
    int mjpeg_data_only_frames;
    int mv_table_index;
    int rl_table_index;
    int rl_chroma_table_index;
    int dc_table_index;
    int use_skip_mb_code;
    int slice_height;
    int first_slice_line;
    int flipflop_rounding;
    int msmpeg4_version;
    int per_mb_rl_table;
    int esc3_level_length;
    int esc3_run_length;
    int(*ac_stats)[2][64 + 1][64 + 1][2];
    int inter_intra_pred;
    int mspel;
    GetBitContext gb;
    int gop_picture_number;
    int last_mv_dir;
    int broken_link;
    uint8_t *vbv_delay_ptr;
    int progressive_sequence;
    int mpeg_f_code[2][2];
    int picture_structure;
    int intra_dc_precision;
    int frame_pred_frame_dct;
    int top_field_first;
    int concealment_motion_vectors;
    int q_scale_type;
    int intra_vlc_format;
    int alternate_scan;
    int repeat_first_field;
    int chroma_420_type;
    int chroma_format;
    int chroma_x_shift;
    int chroma_y_shift;
    int progressive_frame;
    int full_pel[2];
    int interlaced_dct;
    int first_slice;
    int first_field;
    int rtp_mode;
    uint8_t *ptr_lastgob;
    int swap_uv;
    short *pblocks[12];
};

typedef struct MpegEncContext  MpegEncContext;
extern MpegEncContext * restrict s;

void loop()
{
#pragma scop

    for(i = 0; i <((signed int )(sizeof(s -> direct_scale_mv[0]) / sizeof(int16_t ))); i++)
    {
        s -> direct_scale_mv[0][i] =((i -((signed int )(sizeof(s -> direct_scale_mv[0]) / sizeof(int16_t ))) / 2) *(s -> pb_time) /(s -> pp_time));
        s -> direct_scale_mv[1][i] =((i -((signed int )(sizeof(s -> direct_scale_mv[0]) / sizeof(int16_t ))) / 2) *((s -> pb_time) -(s -> pp_time)) /(s -> pp_time));
    }

#pragma endscop
}
