#include <stdio.h>
#define N 100
int x[N], k, n;
void output() {
  for (int i = 0; i < k; ++i) {
    printf("%d ", x[i]);
  }
  printf("\n");
}
void solve(int i) {
  int v = i > 0? x[i - 1] + 1: 0;
  for (; v <= n - k + i; ++v) {
    x[i] = v;
    if (i == k - 1) {
      output();
    } else {
      solve(i + 1);
    }
  }
}
int main() {
  printf("Nhập k, n: ");
  scanf("%d%d", &k, &n);
  solve(0);
  return 0;
}