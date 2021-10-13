#include <stdio.h>
int combinations(int k, int n) {
  if (k == 0 || k == n) {
    return 1;
  }
  return combinations(k - 1, n - 1) +
         combinations(k, n - 1);
}
int main() {
  printf("Nhập k, n: ");
  int k, n;
  scanf("%d%d", &k, &n);
  printf("%d\n", combinations(k, n));
  return 0;
}