#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define MAP_WORD_SIZE 8
#define MIN_SIZE_IN_MEM 2048      // 2 KB
#define MAX_SIZE_IN_MEM_SCALAR 8  // 8 * 2KB = 16 KB
#define EMPTY_SLOT_ID '/'

void fill_mem_chunk(char* mem_chunk, int mem_chunk_size, int process_amount, int allocation_unit_size_in_bytes) {
  srand(time(NULL));
  int filled_slots = 0;
  char current_process_id = 'A';

  for (int i = 0; i < process_amount; i++) {
    int process_slots_amount = ((rand() % MAX_SIZE_IN_MEM_SCALAR) + 1)*(MIN_SIZE_IN_MEM/allocation_unit_size_in_bytes);
    
    for (int j = 0; j < process_slots_amount; j++) {
      mem_chunk[filled_slots] = current_process_id;
      filled_slots++;
    }

    int slots_amount_to_fill = MAP_WORD_SIZE - process_slots_amount;
    for (int j = 0; j < slots_amount_to_fill && filled_slots < mem_chunk_size; j++) {
      mem_chunk[filled_slots] = EMPTY_SLOT_ID;
      filled_slots++;
    }

    current_process_id++;
  }

  while (filled_slots < mem_chunk_size) {
    mem_chunk[filled_slots] = EMPTY_SLOT_ID;
    filled_slots++;
  }

  mem_chunk[mem_chunk_size] = '\0';
}
