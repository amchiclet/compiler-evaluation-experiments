#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
typedef unsigned int wordtype;
typedef wordtype sizetype;
extern sizetype Pos;
typedef void * AddrType;
typedef AddrType addrtype;
typedef wordtype indextype;
typedef indextype chunkindextype;
typedef chunkindextype handletype;
typedef unsigned short unshorttype;
typedef unshorttype idtype;
struct TypeToken
{
    handletype Handle;
    idtype DbId;
    idtype CoreDbId;
};

typedef struct TypeToken  tokentype;
typedef wordtype numtype;
enum TypeTypeTypeDesc {aString=0,aInteger=1,aReal=2,aLink=3,aEnum=4,aBoolean=5,aChunk=6,aDbmsString=7,aValue=8,aAddr=9,aRefObj=10,aNonTypeType=999999999};;
typedef enum TypeTypeTypeDesc typetype;
struct bTreeSetHeadType
{
    addrtype This;
    tokentype Token;
    numtype PrimaryKey;
    numtype Key2ary;
    handletype BuildDesc;
    handletype lOwnerObject;
    sizetype KeySize;
    typetype KeyType;
    idtype TreeDbId;
    numtype TreeOrder;
    numtype TreeNodesDir;
    indextype TreeRootNode;
    sizetype NodeSize;
    numtype NodeCount;
    numtype KeyCount;
    numtype TreeKeysDir;
    numtype MaxKeys;
    numtype MinKeys;
    indextype *TempKeys;
    handletype *TempHandles;
    handletype *TempLeafs;
};

typedef struct bTreeSetHeadType  btreesethead;
typedef btreesethead ltreesethead;
extern ltreesethead * restrict SetHead;
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
extern lbtreenode * restrict SibNode;

void loop()
{
#pragma scop

    for(Pos = SetHead -> MinKeys + 1; Pos <= SetHead -> MaxKeys; ++Pos)
    {
        SibNode -> NodeKeys[Pos - 1 - SetHead -> MinKeys] = SetHead -> TempKeys[Pos];
        SibNode -> NodeHandles[Pos - 1 - SetHead -> MinKeys] = SetHead -> TempHandles[Pos];
        SibNode -> NodeLeafs[Pos - SetHead -> MinKeys] = SetHead -> TempLeafs[Pos + 1];
        ++SibNode -> NumKeys;
    }

#pragma endscop
}
