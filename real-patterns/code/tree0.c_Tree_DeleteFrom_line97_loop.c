#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int Pos;
typedef unsigned int wordtype;
typedef wordtype indextype;
extern indextype KeyPos;
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
extern lbtreenode * restrict DeleteNode;

void loop()
{
#pragma scop

    for(Pos = KeyPos; Pos < DeleteNode -> NumKeys; ++Pos)
    {
        DeleteNode -> NodeKeys[Pos] = DeleteNode -> NodeKeys[Pos + 1];
        DeleteNode -> NodeHandles[Pos] = DeleteNode -> NodeHandles[Pos + 1];
    }

#pragma endscop
}
