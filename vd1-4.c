#include <stdio.h>
int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Usage: ./prog input.txt output.txt\n");
    return 1;
  }
  FILE *inp = fopen(argv[1], "r");
  if (!inp) {
    printf("Lỗi mở tệp %s\n", argv[1]);
    return 1;
  }
  FILE *out = fopen(argv[2], "w");
  if (!out) {
    printf("Lỗi mở tệp %s\n", argv[2]);
    return 1;
  }
  int c;  // trong khoảng [0..255] hoặc -1 (EOF)
  while ((c = fgetc(inp)) != EOF) {
    fputc(c, out);
  }
  fclose(out);
  fclose(inp);
  return 0;
}