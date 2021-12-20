#include "cgen.h"

typedef struct sll_node_d_s {
  struct sln_s base;
  double value;
} *sll_node_d_t;

#define to_sll_node_d(n) ((sll_node_d_t)n)
#define sll_node_d_value(n) (to_sll_node_d(n)->value)

sln_t sll_create_node_d(double value) {
  sln_t tmp = sln_create();
  sll_node_d_t nn = realloc(tmp, sizeof(struct sll_node_d_s));
  nn->value = value;
  return (sln_t)nn;
}

void sll_stack_push_d(sll_t list, double value) {
  sll_push_front(list, sll_create_node_d(value));
}

double sll_stack_top_d(sll_t list) {
  sln_t n = list->front;
  return sll_node_d_value(n);
}

double sll_stack_pop_d(sll_t list) {
  double value = sll_stack_top_d(list);
  sll_pop_front(list);
  return value;
}

void sll_stack_pprint(sll_t list) {
  sll_traverse(cur, list) {
    printf("%lf\n", sll_node_d_value(cur));
  }
  printf("size = %ld\n", sll_length(list));
}

int main() {
  // 10 2 3 - +

  sll_t s = sll_create();
  sll_stack_push_d(s, 10.0);
  sll_stack_push_d(s, 2.0);
  sll_stack_push_d(s, 3.0);
  sll_stack_pprint(s);

  // xử lý phép trừ (-)
  double d1 = sll_stack_pop_d(s),
         d2 = sll_stack_pop_d(s);
  sll_stack_push_d(s, d2 - d1);
  sll_stack_pprint(s);

  // Xử lý phép +
  d1 = sll_stack_pop_d(s);
  d2 = sll_stack_pop_d(s);
  sll_stack_push_d(s, d2 - d1);
  sll_stack_pprint(s);

  sll_free(s);
  return 0;
}