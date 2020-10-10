#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
typedef short int16_t;
typedef struct
{
    int16_t x;
    int16_t y;
    unsigned char layer;
    unsigned char level;
    unsigned char id;
    unsigned char bits_q3;
} od_acct_symbol;
typedef struct
{
    char *str[256];
    int nb_str;
} od_accounting_dict;
typedef struct
{
    od_acct_symbol *syms;
    int nb_syms;
    od_accounting_dict dict;
} od_accounting;
typedef unsigned int uint32_t;
typedef struct
{
    od_accounting acct;
    int nb_syms_alloc;
    int curr_x;
    int curr_y;
    int curr_level;
    int curr_layer;
    uint32_t last_tell;
    int16_t hash_dict[1021];
} od_accounting_internal;
extern od_accounting_internal * restrict acct;

void loop()
{
#pragma scop

    for(i = 0; i < 1021; i++) acct -> hash_dict[i] =(- 1);

#pragma endscop
}
