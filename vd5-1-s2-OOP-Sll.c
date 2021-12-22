#include "OOP/Sll.c"

int main() {
  SllGt list = New(SllGt);
  list->PushBack(list, (gtype){.l = 100});
  list->PushBack(list, (gtype){.l = 200});
  list->PushBack(list, (gtype){.l = 300});
  list->PushFront(list, (gtype){.l = 60});
  Delete(SllGt, list);
  return 0;
}