#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int Pos;
typedef unsigned int wordtype;
typedef wordtype indextype;
typedef wordtype numtype;
typedef indextype chunkindextype;
typedef chunkindextype handletype;
struct lBtreeNodeType
{
    indextype Index;
    indextype ParentNode;
    numtype NumKeys;
    indextype *NodeKeys;
    handletype *NodeHandles;
    indextype *NodeLeafs;
};

typedef struct lBtreeNodeType  lbtreenode;
extern lbtreenode * restrict GtrNode;

void loop()
{
#pragma scop

    for(Pos = 0; Pos < GtrNode -> NumKeys; ++Pos)
    {
        GtrNode -> NodeKeys[Pos] = GtrNode -> NodeKeys[Pos + 1];
        GtrNode -> NodeHandles[Pos] = GtrNode -> NodeHandles[Pos + 1];
    }

#pragma endscop
}
