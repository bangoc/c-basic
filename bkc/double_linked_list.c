#include "double_linked_list.h"

#include <stdlib.h>

dll_node_t dll_create_node() {
  dll_node_t n = malloc(sizeof(struct dll_node_s));
  n->next = n->prev = NULL;
  return n;
}

void dll_free_node(dll_node_t node) {
  free(node);
}

dll_t dll_create_list() {
  dll_t list = malloc(sizeof(struct dll_s));
  list->front = list->back = NULL;
  return list;
}

void dll_free_list(dll_t list) {

}