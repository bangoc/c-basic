/*
  (C) Nguyen Ba Ngoc 2021
*/

#include "cgen.h"
#include "ext/io.h"

#include <ctype.h>
#include <string.h>
#include <stdlib.h>

typedef struct song_s {
  char *name;
  char *singer;
  char *musician;
  int year;
} *song_t;

const char *field_sep = "#*#";
enum {
  SONG_NULL,
  SONG_NAME,
  SONG_SINGER,
  SONG_MUSICIAN,
  SONG_YEAR,
  SONG_ELEMENTS
};
const char *field_names[] = {"", "Tên", "Ca sĩ", "Nhạc sĩ", "Năm", ""};
const int field_width[] = {3, 20, 10, 10, 5, 0};

int estimate_utf8(const char *s) {
  int cc = 0;
  while (*s) {
    if ((*s & 0xC0) != 0x80) {
      ++cc;
    }
    ++s;
  }
  return cc;
}

song_t song_create() {
  song_t song = malloc(sizeof(struct song_s));
  song->name = song->singer = song->musician = NULL;
  return song;
}

void gtype_free_song(gtype value) {
  song_t song = (song_t)(value.v);
  free(song->name);
  free(song->singer);
  free(song->musician);
  free(song);
}

void pprint_utf8(const char *s, int width) {
  int align = width - estimate_utf8(s);
  if (align < 0) {
    align = 0;
  }
  printf("%s%*s", s, align, " ");
}

void gtype_pprint_song(gtype value) {
  song_t song = (song_t)(value.v);
  pprint_utf8(song->name, field_width[SONG_NAME]);
  pprint_utf8(song->singer, field_width[SONG_SINGER]);
  pprint_utf8(song->musician, field_width[SONG_MUSICIAN]);
  printf("%*d", -field_width[SONG_YEAR], song->year);
  printf("\n");
}

void song_list_pprint(gvec_t songs) {
  for (int i = SONG_NULL + 1; i < SONG_ELEMENTS; ++i) {
    pprint_utf8(field_names[i], field_width[i]);
  }
  printf("\n");
  gvec_traverse(g, songs) {
    gtype_pprint_song(*g);
  }
}

void song_list_idx_pprint(gvec_t songs, gvec_t positions) {
  printf("STT  ");
  for (int i = SONG_NULL + 1; i < SONG_ELEMENTS; ++i) {
    pprint_utf8(field_names[i], field_width[i]);
  }
  printf("\n");
  gvec_traverse(cur, positions) {
    printf("%3ld  ", gvec_elem_idx(positions, cur) + 1);
    gtype_pprint_song(gvec_elem(songs, cur->l));
  }
}

#define parse_attrib(line, sign, attrib) \
  do { \
    char *tmp; \
    if ((tmp = strstr(line, sign)) == NULL) { \
      return NULL; \
    } \
    attrib = line; \
    *tmp = 0; \
    line = tmp + strlen(sign); \
  } while (0)

song_t parse_song(char *line) {
  char *name, *singer, *musician, *pyear;
  parse_attrib(line, field_sep, name);
  parse_attrib(line, field_sep, singer);
  parse_attrib(line, field_sep, musician);
  pyear = line;
  int year;
  if (sscanf(pyear, "%d", &year) != 1) {
    return NULL;
  }
  song_t song = song_create();
  song->name = strdup(name);
  song->singer = strdup(singer);
  song->musician = strdup(musician);
  song->year = year;
  return song;
}
#undef parse_attrib

gvec_t parse_songs_list(const char *fname) {
  FILE *f = fopen(fname, "r");
  if (!f) {
    printf("Không thể mở tệp %s\n", fname);
    return NULL;
  }
  gvec_t songs = gvec_create(10, gtype_free_song);
  char *line = NULL;
  song_t tmp;
  while (cgetline(&line, 0, f)) {
    if ((tmp = parse_song(line))) {
      gvec_append(songs, gtype_v(tmp));
    }
  }
  free(line);
  fclose(f);
  return songs;
}

#define to_song(p) ((song_t)(((const gtype*)p)->v))
int song_cmp_name(const void* v1, const void* v2) {
  return strcmp(to_song(v1)->name, to_song(v2)->name);
}
int song_cmp_singer(const void* v1, const void* v2) {
  return strcmp(to_song(v1)->singer, to_song(v2)->singer);
}
int song_cmp_musician(const void* v1, const void* v2) {
  return strcmp(to_song(v1)->musician, to_song(v2)->musician);
}
int song_cmp_year(const void* v1, const void* v2) {
  return to_song(v1)->year - to_song(v2)->year;
}
#undef to_song

int (*song_cmp[])(const void *, const void*) = {NULL,
    song_cmp_name, song_cmp_singer, song_cmp_musician, song_cmp_year};

int select_field() {
  for (int i = SONG_NULL + 1; i < SONG_ELEMENTS; ++i) {
    printf("%d. %s\n", i, field_names[i]);
  }
  int c;
  printf("Lựa chọn của bạn [1-4]: ");
  scanf("%d", &c);
  clear_stdin();
  if (c < 1 || c > 4) {
    return -1;
  }
  return c;
}

void song_view(gvec_t songs) {
  printf("Bạn muốn sắp xếp theo thuộc tính nào: \n");
  int c = select_field();
  if (c < 0) {
    printf("Lựa chọn không hợp lệ.\n");
    return;
  }
  gvec_qsort(songs, song_cmp[c]);
  song_list_pprint(songs);
}

gvec_t song_filter(gvec_t songs) {
  printf("Bạn muốn tìm theo thuộc tính nào: \n");
  int c = select_field();
  if (c < 0) {
    printf("Lựa chọn không hợp lệ.\n");
    return NULL;
  }
  gvec_qsort(songs, song_cmp[c]);
  gvec_t filtered = gvec_create(10, NULL);
  char *sub = NULL;
  int year;
  switch (c) {
    case SONG_NAME:
    case SONG_SINGER:
    case SONG_MUSICIAN:
      printf("Nhập chuỗi truy vấn: ");
      remove_tail_lf(cgetline(&sub, 0, stdin));
      break;
    case SONG_YEAR:
      printf("Nhập năm: ");
      scanf("%d", &year);
      clear_stdin();
      break;
  }
  gvec_traverse(cur, songs) {
    song_t song = (song_t)(cur->v);
    int ok = 0;
    switch (c) {
      case SONG_NAME:
        ok = (strstr(song->name, sub) != NULL);
        break;
      case SONG_SINGER:
        ok = (strstr(song->singer, sub) != NULL);
        break;
      case SONG_MUSICIAN:
        ok = (strstr(song->musician, sub) != NULL);
        break;
      case SONG_YEAR:
        ok = (song->year >= year);
        break;
    }
    if (ok) {
      gvec_append(filtered, gtype_l(gvec_elem_idx(songs, cur)));
    }
  }
  free(sub);
  return filtered;
}

void song_search(gvec_t songs) {
  gvec_t filtered = song_filter(songs);
  if (filtered) {
    song_list_idx_pprint(songs, filtered);
    gvec_free(filtered);
  } else {
    printf("Đã phát sinh lỗi\n");
  }
}

void save_songs(gvec_t songs, const char *fname) {
  FILE *f = fopen(fname, "w");
  if (!f) {
    printf("Lỗi mở tệp %s\n", fname);
    return;
  }
  gvec_traverse(cur, songs) {
    song_t song = (song_t)(cur->v);
    fprintf(f, "%s%s%s%s%s%s%d\n", song->name, field_sep, song->singer,
                  field_sep, song->musician, field_sep, song->year);
  }
  fclose(f);
}

#define cgetline_input(msg, out) \
  printf(msg); \
  remove_tail_lf(cgetline(&(out), 0, stdin))
void song_add(gvec_t songs, const char *fname) {
  song_t song = song_create();
  cgetline_input("Nhập tên: ", song->name);
  cgetline_input("Nhập ca sĩ: ", song->singer);
  cgetline_input("Nhập nhạc sĩ: ", song->musician);
  printf("Nhập năm: ");
  scanf("%d", &(song->year));
  clear_stdin();
  gvec_append(songs, gtype_v(song));
  save_songs(songs, fname);
}
#undef cgetline_input

void song_delete(gvec_t songs, const char *fname) {
  gvec_t positions = song_filter(songs);
  if (!positions) {
    printf("Đã phát sinh lỗi.\n");
    return;
  }
  if (gvec_size(positions) < 1) {
    printf("Không tìm thấy bài hát nào.\n");
    gvec_free(positions);
    return;
  }
  song_list_idx_pprint(songs, positions);
  printf("Nhập chỉ số bài muốn xóa: ");
  int idx = 0;
  scanf("%d", &idx);
  clear_stdin();
  idx -= 1;
  if (idx < 0 || idx >= gvec_size(positions)) {
    printf("Chỉ số không hợp lệ.\n");
    gvec_free(positions);
    return;
  }
  gtype_pprint_song(gvec_elem(songs, idx));
  printf("Bạn thực sự muốn xóa bài này? [y/n]: ");
  int choice = tolower(getchar());
  if (choice == 'y') {
    int real_idx = gvec_elem(positions, idx).l;
    gvec_remove(songs, real_idx);
    save_songs(songs, fname);
    printf("Đã xóa.\n");
  }
  gvec_free(positions);
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: ./prog songs.txt\n");
    return 1;
  }
  char *fname = argv[1];
  gvec_t songs = parse_songs_list(fname);
  if (!songs) {
    printf("Không thể đọc dữ liệu từ %s\n", fname);
    return 1;
  }
  for (;;) {
    printf("Lựa chọn chức năng:\n"
           "1. Xem bài hát\n"
           "2. Lọc danh sách bài hát\n"
           "3. Thêm bài hát\n"
           "4. Xóa bài hát\n"
           "5. Thoát\n"
           "Lựa chọn của bạn [1-5]: ");
    int c = 0;
    scanf("%d", &c);
    clear_stdin();
    if (c == 1) {
      song_view(songs);
    } else if (c == 2) {
      song_search(songs);
    } else if (c == 3) {
      song_add(songs, fname);
    } else if (c == 4) {
      song_delete(songs, fname);
    } else if (c == 5) {
      break;
    } else {
      printf("Lựa chọn không hợp lệ.\n");
    }
  }
  gvec_free(songs);
  return 0;
}