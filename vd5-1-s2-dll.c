#include "cgen.h"

int main() {
  dll_t list = dll_create();
  idl_push_back(list, 10);
  idl_push_back(list, 20);
  idl_push_back(list, 30);
  idl_push_back(list, 5);
  idl_pprint(list);
  dll_free(list);
  return 0;
}