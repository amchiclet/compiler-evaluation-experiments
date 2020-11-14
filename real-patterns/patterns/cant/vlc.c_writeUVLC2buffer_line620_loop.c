#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
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
extern SyntaxElement * restrict se;
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
extern Bitstream * restrict currStream;
extern unsigned int mask;

void loop()
{
#pragma scop

    for(i = 0; i < se -> len; i++)
    {
        currStream -> byte_buf <<= 1;
        if(se -> bitpattern & mask) currStream -> byte_buf |= 1;
        currStream -> bits_to_go--;
        mask >>= 1;
        if(currStream -> bits_to_go == 0)
        {
            currStream -> bits_to_go = 8;
            currStream -> streamBuffer[currStream -> byte_pos++] = currStream -> byte_buf;
            currStream -> byte_buf = 0;
        }
    }

#pragma endscop
}
