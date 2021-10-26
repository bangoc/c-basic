#include "ext/io.h"

int main() {
  FILE *inp = fopen("songs.txt", "r");
  char *line = NULL;
  while (cgetline(&line, 0, inp)) {
    printf("%s", line);
  }
  fclose(inp);
  return 0;
}