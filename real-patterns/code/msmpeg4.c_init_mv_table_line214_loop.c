#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;
struct VLC
{
    int bits;
    int16_t(*table)[2];
    int table_size;
    int table_allocated;
};

typedef struct VLC  VLC;
struct MVTable
{
    int n;
    const uint16_t *table_mv_code;
    const uint8_t *table_mv_bits;
    const uint8_t *table_mvx;
    const uint8_t *table_mvy;
    uint16_t *table_mv_index;
    VLC vlc;
};

typedef struct MVTable  MVTable;
extern MVTable * restrict tab;

void loop()
{
#pragma scop

    for(i = 0; i < 4096; i++) tab -> table_mv_index[i] =(tab -> n);

#pragma endscop
}
