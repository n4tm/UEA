#include "types/bitmap.h"
#include "types/bitmap_linked_list.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_WORD_SIZE 256
#define MAX_WORDS_AMOUNT 1000

void read_word_size(int* word_size);
size_t read_memory_sample(char* memory_sample, int word_size);

int main() {
  int word_size;
  read_word_size(&word_size);

  char* memory_sample = (char*)malloc(sizeof(char)*word_size*MAX_WORDS_AMOUNT);
  size_t mem_sample_len = read_memory_sample(memory_sample, word_size);
  realloc(memory_sample, sizeof(char)*mem_sample_len);
  
  int words_amount = mem_sample_len / word_size;

  bitmap_t* bitmap = (bitmap_t*)malloc(sizeof(bitmap_t));
  init_bitmap(bitmap, memory_sample, words_amount, word_size);

  print_bitmap(*bitmap);

  bitmap_linked_list_t* bitmap_ll = (bitmap_linked_list_t*)malloc(sizeof(bitmap_linked_list_t));
  init_bitmap_linked_list(bitmap_ll, memory_sample);
  print_bitmap_linked_list(*bitmap_ll);

  free(memory_sample);
  dispose_bitmap(bitmap);
  dispose_bitmap_linked_list(bitmap_ll);
}

void read_word_size(int* word_size) {
  printf("\nSize of each word: ");
  scanf("%d", word_size);
  if (*word_size > MAX_WORD_SIZE || *word_size < 2) {
    printf("Please consider 2 <= size <= 256.\n");
    read_word_size(word_size);
  }
}

size_t read_memory_sample(char* memory_sample, int word_size) {
  printf("Memory block sample (use '/' for empty spaces): ");
  scanf("%s", memory_sample);

  size_t memory_sample_len = strlen(memory_sample);
  if (memory_sample_len % word_size != 0) {
    printf("\nPlease enter a sample whose number of digits is a multiple of %d.\n", word_size);
    printf("Current number of digits: %d\n", memory_sample_len);
    read_memory_sample(memory_sample, word_size);
  }
  return memory_sample_len;
}