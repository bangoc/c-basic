#include "cgen.h"
#include "vd7-lisa.h"

#include <stdio.h>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: ./prog text/lisa_all_text.txt\n");
    return 1;
  }
  BENCH("Tìm từ dừng", 1, stop_words(argv[1]));
  return 0;
}