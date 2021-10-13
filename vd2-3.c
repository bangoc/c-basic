#include <stdio.h>
int a[100] = {1, 1};
int fib(int n) {
  if (a[n]) {
    return a[n];
  }
  return (a[n] = fib(n - 1) + fib(n - 2));
}
int main() {
  printf("Nhập n = ");
  int n;
  scanf("%d", &n);
  printf("Fib(%d) = %d\n", n, fib(n));
  return 0;
}
