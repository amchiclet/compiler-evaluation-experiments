#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
typedef int INT_TYPE;
extern INT_TYPE i;
extern INT_TYPE  partial_verify_vals[5] ;
extern INT_TYPE  key_array[1 << 23] ;
extern INT_TYPE  test_index_array[5] ;

void loop()
{
#pragma scop

    for(i = 0; i < 5; i++) partial_verify_vals[i] = key_array[test_index_array[i]];

#pragma endscop
}
