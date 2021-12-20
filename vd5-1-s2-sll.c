/*
  (C) Nguyen Ba Ngoc 2021
*/

#include "cgen.h"

int main() {
  gsl_t list = gsl_create(NULL);
  gsl_push_back(list, (gtype){.i = 100});
  gsl_push_back(list, (gtype){.i = 200});
  gsl_push_back(list, (gtype){.i = 300});
  gsl_push_back(list, (gtype){.i = 125});
  gsl_traverse(cur, list) {
    printf("%ld ", gsn_value(cur).i);
  }
  printf("\n");
  gsl_free(list);
  return 0;
}