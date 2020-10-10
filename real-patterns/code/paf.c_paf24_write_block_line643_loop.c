#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
typedef long int64_t;
typedef int64_t sf_count_t;
typedef struct
{
    int max_blocks;
    int channels;
    int blocksize;
    int read_block;
    int write_block;
    int read_count;
    int write_count;
    sf_count_t sample_count;
    int *samples;
    int *block;
    int data[];
} PAF24_PRIVATE;
extern PAF24_PRIVATE * restrict ppaf24;
extern int channel;
extern unsigned char * restrict cptr;
extern int nextsample;

void loop()
{
#pragma scop

    for(k = 0; k < 10 * ppaf24 -> channels; k++)
    {
        channel = k % ppaf24 -> channels;
        cptr =((unsigned char *)(ppaf24 -> block)) + 32 * channel + 3 *(k / ppaf24 -> channels);
        nextsample = ppaf24 -> samples[k] >> 8;
        cptr[0] = nextsample;
        cptr[1] =(nextsample >> 8);
        cptr[2] =(nextsample >> 16);
    }

#pragma endscop
}
