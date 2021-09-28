#include <stdio.h>

#define N 10

int main(void){
  double a[N];
  printf("Mời nhập %d số:\n", N);
  for(int i=0; i< N; i++) {
    scanf("%lf", &a[i]);
  }
  printf("Các số theo thứ tự ngược lại:\n");
  for(int i = N - 1; i>=0; --i) {
    printf("%g\n", a[i]);
  }
  return 0;
}
