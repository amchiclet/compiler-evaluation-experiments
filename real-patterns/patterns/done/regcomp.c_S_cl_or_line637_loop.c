declare cl_bitmap[];
declare or_with_bitmap[];

for [i] {
  cl_bitmap[i] = cl_bitmap[i] | or_with_bitmap[i];
}
