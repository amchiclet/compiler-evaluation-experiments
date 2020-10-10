#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
typedef long int64_t;
typedef int64_t Int8;
typedef Int8 Int;
extern Int i;
extern Int spos;
typedef unsigned long uint64_t;
typedef uint64_t UInt8;
typedef UInt8 UInt;
typedef char Char;
typedef UInt ** Bag;
typedef struct
{
    UInt isstream;
    UInt isstringstream;
    Int file;
    Char line[4096];
    Int pos;
    Int format;
    Int indent;
    Int hints[3 * 100 + 1];
    Bag stream;
} TypOutputFile;
typedef TypOutputFile * KOutputStream;
extern KOutputStream restrict stream;
extern Char  str[4096] ;

void loop()
{
#pragma scop

    for(i = spos; i < stream -> pos; i++) str[i - spos] = stream -> line[i];

#pragma endscop
}
