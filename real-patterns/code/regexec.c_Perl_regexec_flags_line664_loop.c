#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
typedef int I32;
extern I32 i;
typedef unsigned char U8;
typedef unsigned short U16;
struct regnode
{
    U8 flags;
    U8 type;
    U16 next_off;
};

typedef struct regnode regnode;
typedef unsigned int U32;
struct sv
{
    void *sv_any;
    U32 sv_refcnt;
    U32 sv_flags;
};

typedef struct sv SV;
struct reg_substr_datum
{
    I32 min_offset;
    I32 max_offset;
    SV *substr;
};

struct reg_substr_data
{
    struct reg_substr_datum data[3];
};

struct reg_data
{
    U32 count;
    U8 *what;
    void *data[1];
};

struct regexp
{
    I32 refcnt;
    char **startp;
    char **endp;
    regnode *regstclass;
    I32 minlen;
    I32 prelen;
    U32 nparens;
    U32 lastparen;
    char *precomp;
    char *subbase;
    char *subbeg;
    char *subend;
    U16 naughty;
    U16 reganch;
    struct reg_substr_data *substrs;
    struct reg_data *data;
    regnode program[1];
};

typedef struct regexp regexp;
extern regexp * restrict prog;
extern char * restrict s;
extern char * restrict startpos;

void loop()
{
#pragma scop

    for(i = 0; i <= prog -> nparens; i++)
    {
        if(prog -> endp[i])
        {
            prog -> startp[i] = s +(prog -> startp[i] - startpos);
            prog -> endp[i] = s +(prog -> endp[i] - startpos);
        }
    }

#pragma endscop
}
