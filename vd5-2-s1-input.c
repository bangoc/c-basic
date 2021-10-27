#include "ext/io.h"

#include <string.h>

int main() {
  char *line = NULL;
  cgetline(&line, 0, stdin);
  // Nhập: 1 2.5 3 + -
  /* Xuất:
    1
    2.5
    3
    +
    -
  */
  if (line[strlen(line) - 1] == '\n') {
    line[strlen(line) - 1] = '\0';
  }
  char *tok = strtok(line, " ");
  while (tok) {
    printf("%s\n", tok);
    tok = strtok(NULL, " ");
  }
  free(line);
  return 0;
}