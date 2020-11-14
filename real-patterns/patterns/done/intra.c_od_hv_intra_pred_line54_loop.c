declare pred[];
declare t[];

for [(i, >=4, <=small)] {
  pred[i * small] = t[-small + i * medium];
}
