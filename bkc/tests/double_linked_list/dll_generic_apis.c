#include "double_linked_list.h"

#include "tests/base/utils.h"

int test_dll_create_node() {
  dll_node_t nn = dll_create_node();
  if (!nn) {
    DEBUG_MSG("Null node");
    return 1;
  }
  if (nn->prev || nn->next) {
    return 1;
  }
  return 0;
}

int test_dll_create_list() {
  dll_t list = dll_create_list();
  if (!list) {
    DEBUG_MSG("Null list");
    return 1;
  }
  if (list -> front || list->back) {
    return 1;
  }
  return 0;
}
int test_dll_push_t1() {
  /*
  front
  NULL
  back

  push_back(list, n1)
     front, back
  NULL <= [n1] => NULL

  push_front(list, n2)
         front    back
  NULL <= [n2] <=> [n1] => NULL
  */
  dll_t list = dll_create_list();
  dll_node_t n1 = dll_create_node();
  dll_push_back(list, n1);
  if (list->front != n1 || list->back != n1) {
    DEBUG_MSG("push_back empty list");
    return 1;
  }
  dll_node_t n2 = dll_create_node();
  dll_push_front(list, n2);
  if (list->front != n2 || list->back != n1) {
    DEBUG_MSG("push_front 2 node");
    return 1;
  }
  if (list->front->prev != NULL || list->back->next != NULL) {
    DEBUG_MSG("end condition.");
    return 1;
  }
  dll_free_list(list);
  list = dll_create_list();
  n1 = dll_create_node();
  dll_push_front(list, n1);
  if (list->front != n1 || list->back != n1) {
    DEBUG_MSG("push_front empty list");
    return 1;
  }
  n2 = dll_create_node();
  dll_push_back(list, n2);
  if (list->front != n1 || list->back != n2) {
    DEBUG_MSG("push back 2 nodes");
    return 1;
  }
  if (list->front->prev != NULL || list->back->next != NULL) {
    DEBUG_MSG("end condition.");
    return 1;
  }
  if (list->front != n1 || list->front->next != n2 || list->front->next->next != NULL ||
        list->back != n2 || list->back->prev != n1 || list->back->prev->prev != NULL) {
    DEBUG_MSG("wrong links");
    return 1;
  }
  return 0;
}

int test_dll_pop_t1() {
  dll_t list = dll_create_list();
  dll_node_t n1 = dll_create_node();
  dll_node_t n2 = dll_create_node();
  dll_node_t n3 = dll_create_node();
  dll_push_back(list, n1);
  dll_push_back(list, n2);
  dll_push_back(list, n3);
  dll_pop_back(list);
  if (list->front != n1 || list->back != n2) {
    DEBUG_MSG("pop_back 3 nodes");
    return 1;
  }
  dll_pop_front(list);
  if (list->front != n2 || list->back != n2) {
    DEBUG_MSG("pop_front 2 nodes");
    return 1;
  }
  if (list->front->prev != NULL || list->back->next != NULL) {
    DEBUG_MSG("end condition.");
    return 1;
  }
  dll_pop_front(list);
  if (list->front != NULL || list->back != NULL) {
    DEBUG_MSG("pop 1 node => empty");
    return 1;
  }
  dll_pop_back(list);
  dll_pop_front(list);
  if (list->front != NULL || list->back != NULL) {
    DEBUG_MSG("pop no operations on empty list");
    return 1;
  }
  return 0;
}

int main() {
  ASSERT(test_dll_create_node() == 0, "dll_create_node");
  ASSERT(test_dll_create_list() == 0, "dll_create_list");
  ASSERT(test_dll_push_t1() == 0, "dll_push_t1");
  ASSERT(test_dll_pop_t1() == 0, "dll_pop_t1");
  return 0;
}