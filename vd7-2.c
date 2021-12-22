/*
  (C) Nguyễn Bá Ngọc 2021
  Minh họa sử dụng ánh xạ dựa trên cây đỏ/đen
  Chương trình hỏi người dùng nhập vào từng chuỗi
  ký tự cho tới khi người dùng nhập chuỗi rỗng
  (chỉ nhấn enter). Sau đó chương trình đưa
  ra các chuỗi người dùng đã nhập cùng với số lần
  chuỗi đó được nhập.
*/

#include "cgen.h"
#include "ext/io.h"
#include <stdio.h>
#include <string.h>
int main() {
  char buff[1024];
  printf("Nhập chuỗi ký tự (hoặc chỉ bấm Enter): \n");
  rbm_t words = rbm_create(gtype_cmp_s, gtype_free_s, NULL);
  do {
    remove_tail_lf(fgets(buff, 1024, stdin));
    if (buff[0] == '\0') {
      break;
    }
    char *s = strdup(buff);
    rbm_ires res = rbm_insert(words, gtype_s(s), gtype_l(1));
     if (!res.inserted) {
       res.nd->value.l++;
       free(s);
     }
  } while (1);
  printf("Các từ đã nhập và số lần nhập: \n");
  rbm_traverse(cur, words) {
    printf("%s: %ld\n",
      rbm_node_key(cur).s, rbm_node_value(cur).l);
  }
  rbm_traverse(cur, words) {
    free(rbm_node_key(cur).s);
  }
  rbm_free(words);
  return 0;
}