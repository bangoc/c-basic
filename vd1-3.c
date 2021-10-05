#include <stdio.h>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: ./prog input.txt\n");
    return 1;
  }
  FILE *inp = fopen(argv[1], "r");
  int n;
  fscanf(inp, "%d", &n);
  int sum = 0, x;
  for (int i = 0; i < n; ++i) {
    fscanf(inp, "%d", &x);
    sum += x;
  }
  printf("Tổng các số là: %d\n", sum);
  fclose(inp);
  return 0;
}
