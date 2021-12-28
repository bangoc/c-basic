/*
  Lưu mặt hàng bằng ánh xạ: id -> mặt hàng,
  Lưu giỏ hàng bằng gsl
*/
#include "cgen.h"
#include "ext/io.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct product_s {
  char *id;
  char *name;
  double price;
  int quantity;
} *product_t;

void gtype_free_product(gtype v) {
  product_t ptr = v.v;
  free(ptr->id);
  free(ptr->name);
  free(ptr);
}

product_t parse_product(char *s) {
  product_t ptr = malloc(sizeof(struct product_s));
  ptr->id = strdup(strtok(s, " "));
  ptr->name = strdup(strtok(NULL, " "));
  sscanf(strtok(NULL, " "), "%lf", &ptr->price);
  sscanf(strtok(NULL, " "), "%d", &ptr->quantity);
  return ptr;
}

int parse_input(const char *inp_name, hmap_t out) {
  FILE *inp = fopen(inp_name, "r");
  char *line = NULL;
  cgetline(&line, 0, inp);
  int n = 0;
  sscanf(line, "%d", &n);
  for (int i = 0; i < n; ++i) {
    product_t tmp = parse_product(cgetline(&line, 0, inp));
    hmap_insert(out, gtype_s(tmp->id), gtype_v(tmp));
  }
  fclose(inp);
  free(line);
  return 0;
}

void find_product(hmap_t products) {
  char *id = NULL;
  printf("Nhập mã sản phẩm: ");
  remove_tail_lf(cgetline(&id, 0, stdin));
  gtype *tmp = hmap_value(products, gtype_s(id));
  if (tmp) {
    product_t pp = tmp->v;
    printf("\t%s\t%s\t%.2f\t%d\n",
      pp->id, pp->name, pp->price, pp->quantity);
  } else {
    printf("Không tìm thấy sản phẩm.\n");
  }
  free(id);
}

typedef struct item_s {
  char *name;
  double price;
  int quantity;
} *item_t;

void gtype_free_item(gtype v) {
  item_t item = v.v;
  free(item->name);
  free(item);
}

item_t create_item(const char *name, double price, int quantity) {
  item_t item = malloc(sizeof(struct item_s));
  item->name = strdup(name);
  item->price = price;
  item->quantity = quantity;
  return item;
}

void create_order(hmap_t products) {
  char *id = NULL;
  int quantity;
  gsl_t order = gsl_create(gtype_free_item);
  for (;;) {
    printf("Nhập id: ");
    remove_tail_lf(cgetline(&id, 0, stdin));
    if (strcmp(id, "STOP") == 0) {
      break;
    }
    gtype *tmp = hmap_value(products, gtype_s(id));
    if (!tmp) {
      printf("Không tìm thấy sản phẩm.\n");
      continue;
    }
    product_t pp = tmp->v;
    printf("Nhập vào số lượng: ");
    scanf("%d", &quantity);
    clear_stdin();
    if (quantity < 0 || quantity >= pp->quantity) {
      printf("Số lượng không hợp lệ. \n");
      continue;
    }
    item_t item = create_item(pp->name, pp->price, quantity);
    gsl_push_back(order, gtype_v(item));
  }
  double total = 0;
  printf("Cty XYZ\n\tĐơn hàng bán lẻ\n");
  printf("STT; Tên mặt hàng; Đơn giá; Số lượng; Thành tiền\n");
  int idx = 1;
  gsl_traverse(cur, order) {
    item_t item = cur->v;
    printf("%d; %s; %.2f; %d; %.2f\n", idx, item->name,
        item->price, item->quantity, item->price * item->quantity);
    total += item->price * item->quantity;
    ++idx;
  }
  printf("**************************************************\n");
  printf("Tổng tiền: %.2f\n", total);
  gsl_free(order);
  free(id);
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: ./prog inp.txt\n");
    return 0;
  }
  hmap_t products = hmap_create(gtype_hash_s, gtype_cmp_s,
      NULL, gtype_free_product);
  parse_input(argv[1], products);
  for (;;) {
    printf("1. Xem thông tin mặt hàng\n"
           "2. Tạo đơn hàng\n"
           "3. Thoát\n");
    printf("Lựa chọn của bạn [1-3]: ");
    int choice = 0;
    scanf("%d", &choice);
    clear_stdin();
    if (choice == 1) {
      find_product(products);
    } else if (choice == 2) {
      create_order(products);
    } else if (choice == 3) {
      break;
    } else {
      printf("Lựa chọn không hợp lệ.\n");
    }
  }
  hmap_free(products);
  return 0;
}