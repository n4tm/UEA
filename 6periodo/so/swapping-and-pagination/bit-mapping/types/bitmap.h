#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct bitmap_t {
  int words_amount;
  int each_word_size;
  int** content;

} bitmap_t;

void init_bitmap(bitmap_t* bitmap, const char* memory_sample, int words_amount, int word_size) {
  bitmap->words_amount = words_amount;
  bitmap->each_word_size = word_size;
  bitmap->content = (int**)malloc(sizeof(int*) * words_amount);

  // Mapeamento de bits
  for (int i = 0; i < words_amount; ++i) {
    bitmap->content[i] = (int*)malloc(sizeof(int)*word_size);
    for (int j = 0; j < word_size; ++j) {
      bitmap->content[i][j] = memory_sample[j + i*word_size] != '/';
    }
  }
}

void dispose_bitmap(bitmap_t* bitmap) {
  for (int i = 0; i < bitmap->words_amount; ++i) {
    free(bitmap->content[i]);
  }
  free(bitmap->content);
  free(bitmap);
}

// Para fins de amostragem
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