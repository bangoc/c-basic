/*
  Công cụ sinh dữ liệu cho bài tập 8.1
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Usage: ./prog inp.txt 1000\n");
    return 1;
  }
  FILE *f = fopen(argv[1], "w");
  long n = 0;
  sscanf(argv[2], "%ld", &n);
  srand(time(NULL));
  for (long i = 0; i < n; ++i) {
    fprintf(f, " %.3f", (double)rand()/rand());
  }
  fclose(f);
}