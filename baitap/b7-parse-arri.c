#include "baitap7.h"

#include "cgen.h"
#include "tests/base/utils.h"
#include "tests/bns/bns_gtype_helper.h"

int t1() {
  int a1[] = {1, 2, 3};
  size_t n1 = sizeof(a1)/sizeof(a1[0]);
  bn_tree_t t = bns_parse_arri(a1, n1);
  /*
          1
        2  3
  */
  ASSERT_ECHO(t && bn_edge_height(t) == 1);
  ASSERT(lnr_match_g(t, (gtype[]){gtype_i(1), gtype_i(2), gtype_i(3)}, 3), "lnr match 1 2 3");
  bn_free_tree(&t);

  t = bns_parse_arri((int[]){1, 2, 3, 5, 6, 8, 9}, 7);
  /*
                   5
               2       8
            1    3   6   9
  */
  ASSERT_ECHO(t && bn_edge_height(t) == 2);
  ASSERT(lnr_match_g(t, (gtype[]){gtype_i(1), gtype_i(2), gtype_i(3), gtype_i(5)
                                  , gtype_i(6), gtype_i(8), gtype_i(9)}, 7),
                    "lnr match 1 2 3 5 6 8 9");
  bn_free_tree(&t);
  return 0;
}

int main() {
  ASSERT(t1() == 0, "t1()");
  printf("Test ok.\n");
  return 0;
}