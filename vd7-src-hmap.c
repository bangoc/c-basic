#include "cgen.h"
#include "ext/io.h"
#include "vd7-lisa.h"

struct word_tf {
  char *word;
  long tf;
};

#define TF(p)  (((struct word_tf*)p)->tf)
int word_tf_inc_cmp(const void *p1, const void *p2) {
  return TF(p2) - TF(p1);
}

#define N 10

void b1_parse(FILE *inp, hmap_t words) {
  char buff[1024];
  while (fscanf(inp, "%s", buff) == 1) {
    hmap_ires res = hmap_insert(words, gtype_s(buff), gtype_l(1));
    if (res.inserted) {
      hmap_key_at(words, res.idx)->s = strdup(buff);
    } else {
      hmap_value_at(words, res.idx)->l += 1;
    }
  }
}

struct word_tf *b2_order_by_tf(hmap_t words) {
  long sz = hmap_nnodes(words);
  printf("Số lượng từ duy nhất = %ld\n", sz);
  struct word_tf *a = malloc(sizeof(struct word_tf) * sz);
  long idx = 0;
  hmap_traverse(key, value, words) {
    a[idx].word = key->s;
    a[idx].tf = value->l;
    ++idx;
  }
  qsort(a, idx, sizeof(struct word_tf), word_tf_inc_cmp);
  return a;
}

void b3_output(struct word_tf *a, long n) {
  for (long i = 0; i < n; ++i) {
    printf("%s: %ld\n", a[i].word, a[i].tf);
  }
}

void stop_words(const char *fname) {
  FILE *inp = fopen(fname, "r");
  hmap_t words = hmap_create(gtype_hash_s, gtype_cmp_s, gtype_free_s, NULL);
  b1_parse(inp, words);
  fclose(inp);
  struct word_tf *a = b2_order_by_tf(words);
  b3_output(a, N);

  hmap_free(words);
  free(a);
}