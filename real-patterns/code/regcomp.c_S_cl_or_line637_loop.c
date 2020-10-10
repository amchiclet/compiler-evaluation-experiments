#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
typedef unsigned char U8;
typedef unsigned short U16;
typedef unsigned int U32;
struct regnode_charclass_class
{
    U8 flags;
    U8 type;
    U16 next_off;
    U32 arg1;
    char bitmap[32];
    char classflags[4];
};

extern struct regnode_charclass_class* restrict cl;
extern struct regnode_charclass_class* restrict or_with;

void loop()
{
#pragma scop

    for(i = 0; i < 32; i++) cl -> bitmap[i] |= or_with -> bitmap[i];

#pragma endscop
}
