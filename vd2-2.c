#include <stdio.h>
int fib(int n) {
  if (n == 0 || n == 1) {
    return 1;
  }
  return fib(n - 1) + fib(n - 2);
}
int main() {
  printf("Nhập n = ");
  int n;
  scanf("%d", &n);
  printf("Fib(%d) = %d\n", n, fib(n));
  return 0;
}