#include "cgen.h"
#include "ext/io.h"
#include "vd7-rbm.h"

struct word_tf {
  char *word;
  long tf;
};

#define TF(p)  (((struct word_tf*)p)->tf)
int word_tf_inc_cmp(const void *p1, const void *p2) {
  return TF(p2) - TF(p1);
}

#define N 10

void b1_parse(FILE *inp, rbm_t words) {
  char buff[1024];
  while (fscanf(inp, "%s", buff) == 1) {
    // Mẹo: insert -1 để phân biệt nút đã có và nút mới
    rbm_node_t n = rbm_insert(words, gtype_s(buff), gtype_i(-1));
    if (n->value.i == -1) {
      n->key.s = strdup(buff);
      n->value.i = 1;
    } else {
      n->value.i += 1;
    }
  }
}

struct word_tf *b2_order_by_tf(rbm_t words) {
  long sz = bn_size((bn_tree_t)words);
  printf("Số lượng từ duy nhất = %ld\n", sz);
  struct word_tf *a = malloc(sizeof(struct word_tf) * sz);
  long idx = 0;
  rbm_traverse(cur, words) {
    a[idx].word = cur->key.s;
    a[idx].tf = cur->value.i;
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
  rbm_t words = rbm_create(gtype_cmp_s);
  b1_parse(inp, words);
  fclose(inp);
  struct word_tf *a = b2_order_by_tf(words);
  b3_output(a, N);

  // Giải phóng bộ nhớ
  rbm_traverse(cur, words) {
    free(cur->key.s);
  }
  rbm_free(words);
  free(a);
}