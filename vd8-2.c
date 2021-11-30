/*
  Minh họa hàng đợi ưu tiên
*/

#include "cgen.h"

int gtype_min_d(gtype v1, gtype v2) {
  if (v1.d < v2.d) {
    return 1;
  } else if (v1.d > v2.d) {
    return -1;
  }
  return 0;
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Usage: ./prog inp.txt 10\n");
    return 1;
  }
  FILE *f = fopen(argv[1], "r");
  double val = 0;
  int k = 0;
  sscanf(argv[2], "%d", &k);

  // Đọc dữ liệu
  arr_t(double) v = arr_create(0, double);
  double value;
  while (fscanf(f, "%lf", &value) == 1) {
    arr_append(v, value);
  }
  fclose(f);
  long n = arr_size(v);
  if (k > n) {
    k = n;
  }

BENCH("Thời gian tìm top k", 1,
  p1w_t q = p1w_create(gtype_min_d);
  double *a = ARR(v);
  for (long i = 0; i < n; ++i) {
    if (i < k) {
      p1w_enqueue(q, gtype_d(a[i]));
    } else if (a[i] > p1w_peek(q).d) {
      p1w_root(q, gtype_d(a[i]));
    }
  }

  /* xuất giá trị theo thứ tự giảm dần */
  a = malloc(sizeof(double) * k);
  for (long i = 0; i < k; ++i) {
    a[i] = p1w_dequeue(q).d;
  }
  for (long i = k - 1; i >= 0; --i) {
    printf("%f\n", a[i]);
  }
  free(a);
  p1w_free(q);
 );

  // Giải phóng bộ nhớ
  arr_free(v);
  return 0;
}