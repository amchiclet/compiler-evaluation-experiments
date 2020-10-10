declare Anew_QA[];
declare A_Q24[];

for [k] {
  Anew_QA[k] =
    24 - 16 == 1 ?
    (A_Q24[k] >> 1) + (A_Q24[k] & 1) :
    (A_Q24[k] >> 24 - 16 - 1) + 1 >> 1;
}
