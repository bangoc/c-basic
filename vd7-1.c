#include <stdio.h>
#include <stdlib.h>

void print_a(int *a, const int n) {
  for (int i = 0; i < n; ++i) {
    printf(" %d", a[i]);
  }
  printf("\n");
}

#define to_int(p) (*((const int*)p))
int cmp_inc_i(const void *a, const void *b) {
  return to_int(a) - to_int(b);
}

int main() {
  int a[] = {3, 2, 1, 6, 5, 8};
  int n = sizeof(a)/sizeof(a[0]);
  printf("Trước sắp xếp: ");
  print_a(a, n);
  qsort(a, n, sizeof(a[0]), cmp_inc_i);
  printf("Sau Sắp xếp: ");
  print_a(a, n);
  return 0;
}