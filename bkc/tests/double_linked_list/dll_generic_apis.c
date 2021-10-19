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

int main() {
  ASSERT(test_dll_create_node() == 0, "dll_create_node");
  ASSERT(test_dll_create_list() == 0, "dll_create_list");
  return 0;
}