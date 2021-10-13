#include <stdio.h>
int rsum(int n) {
  if (n == 1) {
    return 1;
  }
  return n + rsum(n - 1);
}
int main() {
  printf("n = ");
  int n;
  scanf("%d", &n);
  printf("%d\n", rsum(n));
  return 0;
}