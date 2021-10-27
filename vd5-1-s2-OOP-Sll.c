#include "OOP/Sll.c"

int main() {
  SllG list = New(SllG);
  list->PushBack(list, (gtype){.i = 100});
  list->PushBack(list, (gtype){.i = 200});
  list->PushBack(list, (gtype){.i = 300});
  list->PushFront(list, (gtype){.i = 60});
  list->PPrint(list);
  Delete(SllG, list);
  return 0;
}