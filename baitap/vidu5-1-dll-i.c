#include "cgen.ic"

int main() {
  dll_t list = dll_create_list();
  dll_push_back_i(list, 10);
  dll_push_back_i(list, 20);
  dll_push_back_i(list, 30);
  dll_push_front_i(list, 5);
  dll_pprint_list_i(list);
  dll_free_list(list);
  return 0;
}