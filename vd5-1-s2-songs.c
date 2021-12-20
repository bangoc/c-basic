#include "cgen.h"

#include <string.h>

typedef struct dll_node_song_s {
  struct dln_s base;
  char *name;
  char *path;
} *dll_node_song_t;

#define to_dll_node_song(n) ((dll_node_song_t)(n))
#define dll_node_song_name(n) (to_dll_node_song(n)->name)
#define dll_node_song_path(n) (to_dll_node_song(n)->path)

dln_t dll_create_node_song(const char *name,
                      const char *path) {
  dln_t tmp = dln_create();
  dll_node_song_t nn = realloc(tmp, sizeof(struct dll_node_song_s));
  nn->name = strdup(name);
  nn->path = strdup(path);
  return to_dln(nn);
}

void dll_push_back_song(dll_t list,
                  const char *name, const char *path) {
  dll_push_back(list, dll_create_node_song(name, path));
}

void dll_pprint_node_song(dln_t node) {
  printf("[%s]", dll_node_song_name(node));
}

void dll_pprint_list_song(dll_t list) {
  dll_traverse(cur, list) {
    dll_pprint_node_song(cur);
    printf("\n");
  }
}

// Chỉ số từ 1
dln_t dll_node_by_id(dll_t list, long id) {
  long len = dll_length(list);
  if (id < 1 || id > len) {
    return NULL;
  }
  dln_t cur = list->front;
  for (int i = 1; i < id; ++i) {
    cur = cur->next;
  }
  return cur;
}

int main() {
  dll_t list = dll_create();
  dll_push_back_song(list, "Chiếc lá thu phai",
                     "/home/nva/musics/chiec-la-thu-phai.mp3");
  dll_push_back_song(list, "Mưa hồng",
                      "/home/nva/musics/mua-hong.mp3");
  dll_push_back_song(list, "Nắng thủy tinh",
                      "/home/nva/musics/nang-thuy-tinh.");
  dll_pprint_list_song(list);

  printf("%s\n", dll_node_song_path(dll_node_by_id(list, 2)));

  dll_traverse(cur, list) {
    dll_node_song_t node = to_dll_node_song(cur);
    free(node->name);
    free(node->path);
  }

  dll_free(list);
  return 0;
}