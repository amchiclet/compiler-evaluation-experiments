declare L_result;
declare x[];

for [k] {
  L_result = (8192 >> 1);
  L_result = L_result +
    e[k + 0] *(- 134) +
    e[k + 1] *(- 374) +
    e[k + 3] *(2054) +
    e[k + 4] *(5741) +
    e[k + 5] *(8192) +
    e[k + 6] *(5741) +
    e[k + 7] *(2054) +
    e[k + 9] *(- 374) +
    e[k + 10] *(- 134);
  L_result = L_result >> 13;
  x[k] =
    L_result < (- 32767 - 1) ?
    (- 32767 - 1) :
    (L_result > 32767?32767 : L_result);
}

