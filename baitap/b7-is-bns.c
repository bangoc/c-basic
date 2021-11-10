#include "baitap7.h"

#include "cgen.h"
#include "tests/base/utils.h"

int t1() {
  bn_node_t n1 = bns_create_node_g(gtype_i(1)),
               n2 = bns_create_node_g(gtype_i(2)),
               n3 = bns_create_node_g(gtype_i(3)),
               n5 = bns_create_node_g(gtype_i(5)),
               n6 = bns_create_node_g(gtype_i(6)),
               n8 = bns_create_node_g(gtype_i(8)),
               n9 = bns_create_node_g(gtype_i(9));

  bn_tree_t t = bns_create_tree_g(NULL, gtype_cmp_i);
  bn_connect2(n2, left, n1, top);
  bn_connect2(n1, left, n3, top);
  t->root = n2;
  /*
        n2
      n1
    n3
  */
  ASSERT(bn_is_bns(t) == 0, "Not a bns");
  n1->left = NULL;
  bn_connect2(n2, right, n3, top);
  /*
        n2
      n1  n3
  */
  ASSERT(bn_is_bns(t) == 1, "bns");

  t->root = n5;
  /*
    n5
  */
  ASSERT(bn_is_bns(t) == 1, "only root");
  bn_connect2(n5, left, n2, top);
  /*
          n5
       n2
     n1   n3
  */
  ASSERT(bn_is_bns(t) == 1, "Bns");
  bn_connect2(n5, right, n6, top);
  bn_connect2(n6, right, n9, top);
  bn_connect2(n9, right, n8, top);
  /*
           n5
       n2      n9
     n1  n3       n8
  */
  ASSERT(bn_is_bns(t) == 0, "Not a Bns");
  n9->right = NULL;
  bn_connect2(n9, left, n8, top);
  /*
           n5
       n2       n9
     n1  n3   n8
  */

  ASSERT(bn_is_bns(t) == 1, "Bns");
  return 0;
}

int main() {
  ASSERT(t1() == 0, "t1()");
  printf("Test Ok!\n");
  return 0;
}