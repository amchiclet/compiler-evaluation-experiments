#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
typedef unsigned long size_t;
extern size_t j;
typedef int int32;
extern int32 blocksize;
extern char * restrict cp;
union anytype_s
{
    void *ptr;
    long i;
    unsigned long ui;
    double fl;
};

typedef union anytype_s  anytype_t;
struct gnode_s
{
    anytype_t data;
    struct gnode_s *next;
};

typedef struct gnode_s  gnode_t;
typedef gnode_t * glist_t;
struct listelem_alloc_s
{
    char **freelist;
    glist_t blocks;
    glist_t blocksize;
    size_t elemsize;
    size_t blk_alloc;
    size_t n_blocks;
    size_t n_alloc;
    size_t n_freed;
};

typedef struct listelem_alloc_s listelem_alloc_t;
extern listelem_alloc_t * restrict list;
extern char ** restrict cpp;

void loop()
{
#pragma scop

    for(j =(blocksize - 1); j > 0; --j)
    {
        cp += list -> elemsize;
        *cpp = cp;
        cpp =((char **)cp);
    }

#pragma endscop
}
