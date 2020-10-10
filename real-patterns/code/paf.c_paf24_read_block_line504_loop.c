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

void loop()
{
#pragma scop

    for(k = 0; k < 10 * ppaf24 -> channels; k++)
    {
        channel = k % ppaf24 -> channels;
        cptr =((unsigned char *)(ppaf24 -> block)) + 32 * channel + 3 *(k / ppaf24 -> channels);
        ppaf24 -> samples[k] =((cptr[0] << 8 | cptr[1] << 16) |((unsigned int )cptr[2]) << 24);
    }

#pragma endscop
}
