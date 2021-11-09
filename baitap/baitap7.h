#ifndef BAITAP7_H_
#define BAITAP7_H_

#include "bns.h"

/*
        n1
      n2  n3
    n4  n5
    x(n1) = 0
    x(n5) = 0
    x(n2) = -1
    x(n3) = 1
  Trả về:
    Khoảng cách theo trục x.
*/
long bn_xdist(bn_tree_t t, bn_node_t n);

/*
  t - là con trỏ tới đối tượng bns_tree_g và các nút
      là những con trỏ tới các đối tượng bns_node_g.
  Trả về: 1 - nếu đúng là cây nhị phân tìm kiếm
          0 - nếu ngược lại (không phải bns).
*/
int bn_is_bns(bn_tree_t t);

/*
  lac = lowest common ancestor/nút trên gần nhất
        n1
     n2     n3
          n5  n6
    bn_lca(n5, n6) => n3
    bn_lca(n2, n6) => n1
    bn_lca(n1, n2) => NULL
  Trả về:
     lca của n1 và n2 nếu có, hoặc trả về NULL trong
     trường hợp ngược lại.
*/
bn_node_t bn_lca(bn_node_t n1, bn_node_t n2);

/*
  a và n là con trỏ và số lượng phần tử của mảng.
  Các phần tử trong mảng đã được sắp xếp theo thứ tự tăng dần.
  Trả về:
    Con trỏ kiểu bn_tree_t và trỏ tới đối tượng bns_tree_g
    với các nút có kiểu bns_node_g_t.
    Trong trường hợp có lỗi thì trả về NULL.
*/
bn_tree_t bns_parse_arri(int *a, size_t n);

#endif  // BAITAP7_H_