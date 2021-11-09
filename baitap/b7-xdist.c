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
  ASSERT(bn_xdist(t, n5) == 0, "xdist n5 == 0");
  ASSERT(bn_xdist(t, n3) == -1, "xdist n3");
  ASSERT(bn_xdist(t, n6) == 1, "xdist n6");
  /*
             n5
      n3           n6
   n2          n4        n7
      n1           n8        n9
                                 n10
  */
  ASSERT(bn_xdist(t, n2) == -2, "n2: -2");
  ASSERT(bn_xdist(t, n1) == -1, "n1: -1");
  ASSERT(bn_xdist(t, n4) == 0, "n4: 0");
  ASSERT(bn_xdist(t, n8) == 1, "n8: 1");
  ASSERT(bn_xdist(t, n9) == 3, "n9: 3");
  ASSERT(bn_xdist(t, n10) == 4, "n10: 4");
  return 0;
}

int main() {
  ASSERT(t1() == 0, "t1()");
  printf("Test Ok!\n");
  return 0;
}