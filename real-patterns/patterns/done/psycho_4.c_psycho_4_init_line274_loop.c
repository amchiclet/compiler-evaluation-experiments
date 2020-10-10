declare tmn[];
declare cbval[];

for [j] {
  tmn[j] = 15.5 + cbval[j] > 24.5 ? 15.5 + cbval[j] : 24.5;
}
