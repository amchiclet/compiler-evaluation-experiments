#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
typedef struct
{
    unsigned char *header;
    long header_len;
    unsigned char *body;
    long body_len;
} ogg_page;
extern ogg_page * restrict og;
typedef unsigned int uint32_t;
typedef uint32_t ogg_uint32_t;
extern ogg_uint32_t crc_reg;
extern unsigned int crc_lookup[256];

void loop()
{
#pragma scop

    for(i = 0; i < og -> header_len; i++) crc_reg = crc_reg << 8 ^ crc_lookup[crc_reg >> 24 & 0xff ^ og -> header[i]];

#pragma endscop
}
