#include "cgen.h"

#include <stdlib.h>
#include <time.h>

void rands(char *s, const int n) {
  for (int i = 0; i < n; ++i) {
    s[i] = 'a' + rand() % ('z' - 'a') + 1;
  }
  s[n] = 0;
}

int rand_price() {
  return 10000 + rand() % 1000000;
}

int rand_quant() {
  return 1 + rand() % 1000;
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Usage: ./gen 20000 b11.txt\n");
    return 1;
  }
  int n = 0;
  sscanf(argv[1], "%d", &n);
  FILE *out = fopen(argv[2], "w");
  srand(time(NULL));
  char buff1[30], buff2[30];
  fprintf(out, "%d\n", n);
  hset_t keys = hset_create(gtype_hash_s, gtype_cmp_s, gtype_free_s);
  for (int i = 0; i < n; ++i) {
    for (;;) {
      rands(buff1, 10);
      if (hset_contains(keys, gtype_s(buff1))) {
        continue;
      }
      hset_insert(keys, gtype_s(strdup(buff1)));
      break;
    }
    rands(buff2, 20);
    fprintf(out, "%s %s %d %d\n", buff1, buff2, rand_price(), rand_quant());
  }
  fclose(out);
  hset_free(keys);
  return 0;
}