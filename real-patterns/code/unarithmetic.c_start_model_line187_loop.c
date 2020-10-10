#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int  char_to_index[256] ;
extern unsigned char  index_to_char[256 + 1 + 1] ;

void loop()
{
#pragma scop

    for(i = 0; i < 256; i++)
    {
        char_to_index[i] = i + 1;
        index_to_char[i + 1] =((unsigned char )i);
    }

#pragma endscop
}
