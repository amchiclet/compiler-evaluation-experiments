#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
typedef unsigned int wordtype;
typedef wordtype sizetype;
extern sizetype Pos;
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
extern lbtreenode * restrict LeafNode;
extern indextype KeyPos;

void loop()
{
#pragma scop

    for(Pos = LeafNode -> NumKeys; Pos > KeyPos; --Pos)
    {
        LeafNode -> NodeKeys[Pos] = LeafNode -> NodeKeys[Pos - 1];
        LeafNode -> NodeHandles[Pos] = LeafNode -> NodeHandles[Pos - 1];
    }

#pragma endscop
}
