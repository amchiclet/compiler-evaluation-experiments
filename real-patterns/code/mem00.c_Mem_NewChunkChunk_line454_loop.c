#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
typedef unsigned int wordtype;
typedef wordtype numtype;
typedef numtype chunknumtype;
typedef chunknumtype chunknum;
extern chunknum ChunkChunk;
extern numtype ChunkAddrChunk;
extern numtype NumChunkChunks;
typedef void * AddrType;
typedef AddrType addrtype;
typedef unsigned int FarLongType;
typedef FarLongType farlongtype;
typedef farlongtype longtype;
typedef longtype chunkflags;
typedef wordtype sizeinbytes;
typedef wordtype indextype;
struct Ory
{
    addrtype *ChunkAddr;
    numtype *NextChunk;
    chunkflags *Flags;
    sizeinbytes *UnitSize;
    indextype *UnitCount;
    indextype *StackPtr;
    numtype *StringText;
    indextype *ExtendQty;
    sizeinbytes *MaxUnitLen;
    indextype NextFree;
};

typedef struct Ory  OryType;
extern OryType * restrict Theory;

void loop()
{
#pragma scop

    for(ChunkChunk = ChunkAddrChunk; ChunkChunk < NumChunkChunks; ChunkChunk++)
    {
        ++ *((indextype *)(((char *)Theory -> ChunkAddr[ChunkChunk]) - 20));
    }

#pragma endscop
}
