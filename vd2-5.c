#include <stdio.h>
#define N 100
char x[N];
int n;
void output() {
  for (int i = 0; i < n; ++i) {
    printf("%d", (int)x[i]);
  }
  printf("\n");
}
void solve(int i) {
  for (char v = 0; v < 2; ++v) {
    x[i] = v;
    if (i == n - 1) {
      output();
    } else {
      solve(i + 1);
    }
  }
}
int main() {
  printf("Nhap n = ");
  scanf("%d", &n);
  solve(0);
  return 0;
}