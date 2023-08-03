#include "mem_chunk_manager.h"
#include "types/bitmap.h"
#include "types/bitmap_linked_list.h"

#include <stdlib.h>
#include <unistd.h>

#define ALLOCATION_UNIT_SIZE_IN_BYTES 2048                                 // 1 KB
#define MEM_CHUNK_SIZE 64*(MIN_SIZE_IN_MEM/ALLOCATION_UNIT_SIZE_IN_BYTES)  // Each allocation unit has 2 KB (2048 bytes)
#define PROCESS_AMOUNT 10

int main() {
  while (1) {
    char memory_chunk[MEM_CHUNK_SIZE + 1];
    fill_mem_chunk(memory_chunk, MEM_CHUNK_SIZE, PROCESS_AMOUNT, ALLOCATION_UNIT_SIZE_IN_BYTES);
    
    bitmap_t* bitmap = (bitmap_t*)malloc(sizeof(bitmap_t));
    init_bitmap(bitmap, memory_chunk, MAP_WORD_SIZE * (MIN_SIZE_IN_MEM / ALLOCATION_UNIT_SIZE_IN_BYTES), MAP_WORD_SIZE);

    print_bitmap(*bitmap);

    bitmap_linked_list_t* bitmap_ll = (bitmap_linked_list_t*)malloc(sizeof(bitmap_linked_list_t));
    init_bitmap_linked_list(bitmap_ll, memory_chunk);
    print_bitmap_linked_list(*bitmap_ll);

    dispose_bitmap(bitmap);
    dispose_bitmap_linked_list(bitmap_ll);
    
    sleep(2);
  }
}