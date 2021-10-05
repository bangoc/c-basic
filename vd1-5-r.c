#include <stdio.h>
struct sinhvien {
  int mssv;
  char hoten[64];
};
int main() {
  struct sinhvien a[2];
  FILE *inp = fopen("sv.dat", "rb");
  int n;
  fread(&n, sizeof(n), 1, inp);
  fread(a, sizeof(struct sinhvien), n, inp);
  printf("%8s%32s\n", "STT", "Ho ten");
  for (int i = 0; i < n; ++i) {
    printf("%8d%32s\n", a[i].mssv, a[i].hoten);
  }
  fclose(inp);
  return 0;
}