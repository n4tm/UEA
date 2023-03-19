#include <stdbool.h>

typedef struct page_t {
  int size;
  bool referenced;
  bool modified;
} page_t;