#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
typedef int int32;
extern int32 j;
extern int32 n_hist;
extern int32 * restrict history;
typedef unsigned char uint8;
typedef unsigned int uint32;
typedef signed char int8;
struct logadd_s
{
    void *table;
    uint32 table_size;
    uint8 width;
    int8 shift;
};

typedef struct logadd_s logadd_t;
typedef unsigned long size_t;
struct mmio_file_s
{
    void *ptr;
    size_t mapsize;
};

typedef struct mmio_file_s mmio_file_t;
typedef double float64;
struct logmath_s
{
    logadd_t t;
    int refcount;
    mmio_file_t *filemap;
    float64 base;
    float64 log_of_base;
    float64 log10_of_base;
    float64 inv_log_of_base;
    float64 inv_log10_of_base;
    int32 zero;
};

typedef struct logmath_s logmath_t;
typedef float float32;
struct hash_entry_s
{
    const char *key;
    size_t len;
    void *val;
    struct hash_entry_s *next;
};

typedef struct hash_entry_s  hash_entry_t;
typedef struct
{
    hash_entry_t *table;
    int32 size;
    int32 inuse;
    int32 nocase;
} hash_table_t;
struct ngram_hash_s
{
    int32 wid;
    int32 prob1;
    int32 next;
};

struct ngram_class_s
{
    int32 tag_wid;
    int32 start_wid;
    int32 n_words;
    int32 *prob1;
    struct ngram_hash_s *nword_hash;
    int32 n_hash;
    int32 n_hash_inuse;
};

struct ngram_funcs_s {};

struct ngram_model_s
{
    int refcount;
    int32 *n_counts;
    int32 n_1g_alloc;
    int32 n_words;
    uint8 n;
    uint8 n_classes;
    uint8 writable;
    uint8 flags;
    logmath_t *lmath;
    float32 lw;
    int32 log_wip;
    int32 log_uw;
    int32 log_uniform;
    int32 log_uniform_weight;
    int32 log_zero;
    char **word_str;
    hash_table_t *wid;
    int32 *tmp_wids;
    struct ngram_class_s **classes;
    struct ngram_funcs_s *funcs;
};

typedef struct ngram_model_s ngram_model_t;
struct ngram_model_set_s
{
    ngram_model_t base;
    int32 n_models;
    int32 cur;
    ngram_model_t **lms;
    char **names;
    int32 *lweights;
    int32 **widmap;
    int32 *maphist;
};

typedef struct ngram_model_set_s  ngram_model_set_t;
extern ngram_model_set_t * restrict set;

void loop()
{
#pragma scop

    for(j = 0; j < n_hist; ++j)
    {
        if(history[j] == - 1) set -> maphist[j] = - 1;
        else set -> maphist[j] = set -> widmap[history[j]][set -> cur];
    }

#pragma endscop
}
