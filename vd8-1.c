/*
  Minh họa hàng đợi ưu tiên
*/

#include "cgen.h"

int gtype_max_d(gtype v1, gtype v2) {
  if (v1.d < v2.d) {
    return -1;
  } else if (v1.d > v2.d) {
    return 1;
  }
  return 0;
}

int main() {
  p1w_t q = p1w_create(gtype_max_d);
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