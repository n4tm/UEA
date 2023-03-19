#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "bitmap_linked_list.h"

typedef struct bitmap_t {
  int** content;
  int words_amount;
  int each_word_size;
  bitmap_linked_list_t (*as_linked_list)();
} bitmap_t;

bitmap_linked_list_t as_linked_list();

void init_bitmap(bitmap_t* bitmap, const char* memory_sample, int words_amount, int word_size) {
  bitmap->as_linked_list = as_linked_list;
  bitmap->each_word_size = word_size;
  bitmap->words_amount = words_amount;
  bitmap->content = (int**)malloc(sizeof(int*) * words_amount);

  // Mapeamento de bits
  for (int i = 0; i < words_amount; ++i) {
    bitmap->content[i] = (int*)malloc(sizeof(int)*word_size);
    for (int j = 0; j < word_size; ++j) {
      bitmap->content[i][j] = memory_sample[j + i*word_size] != '/';
    }
  }
}

bitmap_linked_list_t as_linked_list() {
  // TODO
}

void print_bitmap(bitmap_t bitmap) {
  printf("\nBit mapping:\n\n");
  for (int i = 0; i < bitmap.words_amount; ++i) {
    printf("| ");
    for (int j = 0; j < bitmap.each_word_size; ++j) {
      printf("%d ", bitmap.content[i][j]);
    }
    printf("|\n");
  }
  printf("\n");
}