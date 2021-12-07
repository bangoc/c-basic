#include "OOP/Sll.c"

int main() {
  SllGt list = New(SllGt);
  list->PushBack(list, (gtype){.i = 100});
  list->PushBack(list, (gtype){.i = 200});
  list->PushBack(list, (gtype){.i = 300});
  list->PushFront(list, (gtype){.i = 60});
  Delete(SllGt, list);
  return 0;
}