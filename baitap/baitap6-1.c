#include "cgen.ic"

void bn_pprint_node(bn_node_t n) {
  printf("%p\n", n);
}

int main() {
  bn_node_t n1 = bn_create_node();
  bn_node_t n2 = bn_create_node();
  n1->left = n2;
  n2->top = n1;
  bn_node_t n3 = bn_create_node();
  bn_connect2(n1, right, n3, top);

  bn_tree_t t = bn_create_tree(n1);
  /*
    Sinh viên tiếp tục hoàn thành bài tập.
  */

  bn_pprint(t, bn_pprint_node);

  bn_free_tree(&t);
  return 0;
}