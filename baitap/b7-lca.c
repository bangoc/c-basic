#include "baitap7.h"

#include "cgen.ic"
#include "tests/base/utils.h"

int t1() {
  bn_node_t n1 = bn_create_node(),
            n2 = bn_create_node(),
            n3 = bn_create_node(),
            n4 = bn_create_node(),
            n5 = bn_create_node(),
            n6 = bn_create_node(),
            n7 = bn_create_node(),
            n8 = bn_create_node(),
            n9 = bn_create_node(),
            n10 = bn_create_node();
  bn_tree_t t = bn_create_tree(n5);
  bn_connect2(n5, left, n3, top);
  bn_connect2(n5, right, n6, top);
  bn_connect2(n3, left, n2, top);
  bn_connect2(n2, right, n1, top);
  bn_connect2(n6, left, n4, top);
  bn_connect2(n6, right, n7, top);
  bn_connect2(n4, right, n8, top);
  bn_connect2(n7, right, n9, top);
  bn_connect2(n9, right, n10, top);
  /*
             n5
      n3           n6
   n2          n4        n7
      n1           n8        n9
                                 n10
  */
  ASSERT_ECHO(bn_lca(n1, n2) == n3);
  ASSERT_ECHO(bn_lca(n3, n6) == n5);
  ASSERT_ECHO(bn_lca(n3, n5) == NULL);
  ASSERT_ECHO(bn_lca(n8, n9) == n6);
  ASSERT_ECHO(bn_lca(n10, n9) == n7);
  ASSERT_ECHO(bn_lca(n10, n1) == n5);
  bn_free_tree(&t);
  return 0;
}

int main() {
  ASSERT(t1() == 0, "t1()");
  printf("Test ok.\n");
  return 0;
}