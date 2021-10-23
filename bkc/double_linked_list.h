#ifndef DOUBLE_LINKED_LIST_H_
#define DOUBLE_LINKED_LIST_H_

/*
  (c) Nguyen Ba Ngoc, 2021
  Mục tiêu: Thiết kế giao diện sao cho người dùng không cần biết đến
  biểu diễn bên trong của cấu trúc dữ liệu.
*/

typedef struct dll_node_s {
  struct dll_node_s *next;
  struct dll_node_s *prev;
} *dll_node_t;

typedef struct dll_s {
  dll_node_t front;
  dll_node_t back;
} *dll_t;

#define to_dll(n) ((dll_node_t)n)

/* Giao diện khái quát */

dll_node_t dll_create_node();
void dll_free_node(dll_node_t node);
dll_t dll_create_list();
void dll_free_list(dll_t list);

void dll_push_back(dll_t list, dll_node_t nn);
void dll_push_front(dll_t list, dll_node_t nn);
void dll_pop_back(dll_t list);
void dll_pop_front(dll_t list);
dll_node_t dll_front(dll_t list);
dll_node_t dll_back(dll_t list);
dll_node_t dll_inserta(dll_t list, dll_node_t pos, dll_node_t nn);
dll_node_t dll_insertb(dll_t list, dll_node_t pos, dll_node_t nn);
int dll_is_empty(dll_t list);
long dll_length(dll_t list);
void dll_erase(dll_t list, dll_node_t pos);
void dll_clear(dll_t list);

/* Giao diện cho kiểu int */

typedef struct dll_node_i_s {
  struct dll_node_s base;
  int value;
} *dll_node_i_t;

#define to_node_i(n) ((dll_node_i_t)n)
#define node_i_value(n) to_node_i(n)->value

dll_node_t dll_create_node_i(int value);

void dll_push_back_i(dll_t list, int value);
void dll_push_front_i(dll_t list, int value);
int dll_pop_back_i(dll_t list);
int dll_pop_front_i(dll_t list);
int dll_front_i(dll_t list);
int dll_back_i(dll_t list);
dll_node_t dll_inserta_i(dll_t list, dll_node_t pos, int value);
dll_node_t dll_insertb_i(dll_t list, dll_node_t pos, int value);

#endif  // DOUBLE_LINKED_LIST_H_
