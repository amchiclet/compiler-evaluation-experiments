#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int length;
extern int seed;
extern int idx;
extern int exc_mask;
extern short* restrict residual;
extern int* restrict exc_buf_Q10;
extern int Gain_Q16;

void loop()
{
#pragma scop

    for(i = 0; i < length; i++)
    {
        seed =((int )(((unsigned int )907633515) +((unsigned int )(((unsigned int )seed) *((unsigned int )196314165)))));
        idx =((int )(seed >> 24 & exc_mask));;;
        residual[i] =((short )((((10 == 1?((exc_buf_Q10[idx] >> 16) *((int )((short )Gain_Q16)) +((exc_buf_Q10[idx] & 0x0000FFFF) *((int )((short )Gain_Q16)) >> 16) + exc_buf_Q10[idx] *((16 == 1?(Gain_Q16 >> 1) +(Gain_Q16 & 1) :(Gain_Q16 >> 16 - 1) + 1 >> 1)) >> 1) +((exc_buf_Q10[idx] >> 16) *((int )((short )Gain_Q16)) +((exc_buf_Q10[idx] & 0x0000FFFF) *((int )((short )Gain_Q16)) >> 16) + exc_buf_Q10[idx] *((16 == 1?(Gain_Q16 >> 1) +(Gain_Q16 & 1) :(Gain_Q16 >> 16 - 1) + 1 >> 1)) & 1) :((exc_buf_Q10[idx] >> 16) *((int )((short )Gain_Q16)) +((exc_buf_Q10[idx] & 0x0000FFFF) *((int )((short )Gain_Q16)) >> 16) + exc_buf_Q10[idx] *((16 == 1?(Gain_Q16 >> 1) +(Gain_Q16 & 1) :(Gain_Q16 >> 16 - 1) + 1 >> 1)) >> 10 - 1) + 1 >> 1)) > 0x7FFF?0x7FFF :((((10 == 1?((exc_buf_Q10[idx] >> 16) *((int )((short )Gain_Q16)) +((exc_buf_Q10[idx] & 0x0000FFFF) *((int )((short )Gain_Q16)) >> 16) + exc_buf_Q10[idx] *((16 == 1?(Gain_Q16 >> 1) +(Gain_Q16 & 1) :(Gain_Q16 >> 16 - 1) + 1 >> 1)) >> 1) +((exc_buf_Q10[idx] >> 16) *((int )((short )Gain_Q16)) +((exc_buf_Q10[idx] & 0x0000FFFF) *((int )((short )Gain_Q16)) >> 16) + exc_buf_Q10[idx] *((16 == 1?(Gain_Q16 >> 1) +(Gain_Q16 & 1) :(Gain_Q16 >> 16 - 1) + 1 >> 1)) & 1) :((exc_buf_Q10[idx] >> 16) *((int )((short )Gain_Q16)) +((exc_buf_Q10[idx] & 0x0000FFFF) *((int )((short )Gain_Q16)) >> 16) + exc_buf_Q10[idx] *((16 == 1?(Gain_Q16 >> 1) +(Gain_Q16 & 1) :(Gain_Q16 >> 16 - 1) + 1 >> 1)) >> 10 - 1) + 1 >> 1)) <((short )0x8000)?((short )0x8000) :((10 == 1?((exc_buf_Q10[idx] >> 16) *((int )((short )Gain_Q16)) +((exc_buf_Q10[idx] & 0x0000FFFF) *((int )((short )Gain_Q16)) >> 16) + exc_buf_Q10[idx] *((16 == 1?(Gain_Q16 >> 1) +(Gain_Q16 & 1) :(Gain_Q16 >> 16 - 1) + 1 >> 1)) >> 1) +((exc_buf_Q10[idx] >> 16) *((int )((short )Gain_Q16)) +((exc_buf_Q10[idx] & 0x0000FFFF) *((int )((short )Gain_Q16)) >> 16) + exc_buf_Q10[idx] *((16 == 1?(Gain_Q16 >> 1) +(Gain_Q16 & 1) :(Gain_Q16 >> 16 - 1) + 1 >> 1)) & 1) :((exc_buf_Q10[idx] >> 16) *((int )((short )Gain_Q16)) +((exc_buf_Q10[idx] & 0x0000FFFF) *((int )((short )Gain_Q16)) >> 16) + exc_buf_Q10[idx] *((16 == 1?(Gain_Q16 >> 1) +(Gain_Q16 & 1) :(Gain_Q16 >> 16 - 1) + 1 >> 1)) >> 10 - 1) + 1 >> 1)))))));
    }

#pragma endscop
}
