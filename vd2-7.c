#include <stdio.h>

#define N 100
int x[N];
char m[N] = {0};
int n;

void output() {
  for (int i = 0; i < n; ++i) {
    printf("%d ", x[i]);
  }
  printf("\n");
}
void solve(int i) {
  for (int v = 0; v < n; ++v) {
    if (m[v]) {
      continue;
    }
    x[i] = v;
    m[v] = 1;
    if (i == n - 1) {
      output();
    } else {
      solve(i + 1);
    }
    m[v] = 0;
  }
}

int main() {
  printf("Nhap n: ");
  scanf("%d", &n);
  solve(0);
  return 0;
}