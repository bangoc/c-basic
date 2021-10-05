#include <stdio.h>
struct sinhvien {
  int mssv;
  char hoten[64];
};
int main() {
  struct sinhvien a[2] = {
    {1, "Nguyen Van A"},
    {2, "Tran Thi B"}
  };
  FILE *out = fopen("sv.dat", "wb");
  int n = sizeof(a)/sizeof(struct sinhvien);
  fwrite(&n, sizeof(n), 1, out);
  fwrite(a, sizeof(struct sinhvien), n, out);
  return 0;
}