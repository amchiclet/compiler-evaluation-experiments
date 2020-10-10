declare clp[];

for [i] {
  clp[i] = ((i < 0?0 :((i > 255?255 : i))));
}
