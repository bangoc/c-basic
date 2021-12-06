/*
  Minh họa hàng đợi ưu tiên
*/

#include "cgen.h"

int main() {
  p1w_t q = p1w_create(PRIORITY_MAX, gtype_cmp_d);
  p1w_enqueue(q, gtype_d(1.0));
  p1w_enqueue(q, gtype_d(3.0));
  p1w_enqueue(q, gtype_d(2.0));
  while (!p1w_is_empty(q)) {
    gtype value = p1w_dequeue(q);
    printf("%f\n", value.d);
  }
  p1w_free(q);
  return 0;
}