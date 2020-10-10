declare val;
declare valS;
declare valM;
declare succ;
declare fld;
declare ptr[];

for [i] {
  val = ptr[i] >> 16;
  valS =
    val == 0 || valM == 0 ?
    0 :
    val - 1 <= succ - valM ? val - 1 + valM : val - 1 - (succ - valM);
  ptr[i] = (valS << 16) + (fld << 3) + 0x02;
}
