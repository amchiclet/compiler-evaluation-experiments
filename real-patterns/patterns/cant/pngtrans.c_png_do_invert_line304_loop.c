declare rp[];

for [(i, +=4)] {
  rp[i+offset] = ~rp[i+offset];
  rp[i+offset+1] = ~rp[i+offset+1];
  
}
