#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
typedef unsigned int uint32_t;
typedef uint32_t UInt4;
extern UInt4 i;
extern UInt4 len;
typedef int int32_t;
typedef int32_t Int4;
extern Int4 ch;
typedef char Char;
extern Char * restrict ptr;
typedef long int64_t;
typedef int64_t Int8;
typedef Int8 Int;
extern Int seen_nl;
extern UInt4 old;
extern UInt4 crc;
extern UInt4 new;
extern UInt4  syCcitt32[256] ;

void loop()
{
#pragma scop

    for(i = 0; i < len; i++)
    {
        ch =((Int4 )ptr[i]);
        if(ch == '\377' || ch == 10 || ch == 13) ch = '\n';
        if(ch == 10)
        {
            if(seen_nl) continue;
            else seen_nl = 1;
        }
        else seen_nl = 0;
        old =((crc >> 8) & 0x00FFFFFFL);
        new = syCcitt32[((UInt4 )(crc ^ ch)) & 0xff];
        crc = old ^ new;
    }

#pragma endscop
}
