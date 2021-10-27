#include "cgen.ic"

int main() {
  sll_t list = sll_create_list();
  sll_push_back_g(list, (gtype){.i = 100});
  sll_push_back_g(list, (gtype){.i = 200});
  sll_push_back_g(list, (gtype){.i = 300});
  sll_push_front_g(list, (gtype){.i = 125});
  sll_node_t cur = list->front;
  for (; cur != NULL; cur = cur->next) {
    printf("%ld ", sll_node_g_value(cur).i);
  }
  printf("\n");
  sll_free_list(list);
  return 0;
}