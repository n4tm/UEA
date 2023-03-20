#include "mem_node.h"
#include "string.h"

#define BUFFER_HORIZONTAL_THRESHOLD 5

// Dúvida: é preciso implementar os métodos de uma linked list
// (ex: pop, remove) mesmo que não cheguem a ser utilizados?
typedef struct bitmap_linked_list_t {
  mem_node_t* head;
} bitmap_linked_list_t;

void init_bitmap_linked_list(bitmap_linked_list_t* bitmap_ll, const char* memory_sample) {
  int digit_count = 1;
  mem_node_t* current;
  bool is_first_node = true;

  char current_digit = ' ';
  for (int i = 1; current_digit != '\0'; ++i) {
    current_digit = memory_sample[i];
    char last_digit = memory_sample[i-1];
    if (current_digit != last_digit) {
      if (is_first_node) {
        bitmap_ll->head = (mem_node_t*)malloc(sizeof(mem_node_t));
        *(bitmap_ll->head) = (mem_node_t){
          (mem_node_t*)malloc(sizeof(mem_node_t)),  // next
          last_digit != '/' ? 'P' : 'L',            // type
          0,                                        // start_index
          digit_count                               // length
        };
        current = bitmap_ll->head;
        is_first_node = false;
      } else {
        *(current->next) = (mem_node_t){
          (mem_node_t*)malloc(sizeof(mem_node_t)),  // next
          last_digit != '/' ? 'P' : 'L',            // type
          i-digit_count,                            // start_index
          digit_count                               // length
        };
        current = current->next;
      }
      digit_count = 1;
    } else digit_count++;
  }
  current->next = NULL; // Último nó deve referenciar NULL
  free(current->next);
}

void dispose_bitmap_linked_list(bitmap_linked_list_t* bitmap_ll) {
  mem_node_t* current = bitmap_ll->head;
  while (current != NULL) {
    free(current);
    current = current->next;
  }
  free(bitmap_ll);
}

// Para fins de amostragem
void print_bitmap_linked_list(bitmap_linked_list_t bitmap_ll) {
  printf("\nBit mapping as linked list:\n\n");
  int count_until_threshold = 0;
  mem_node_t* current = bitmap_ll.head;
  while (current != NULL) {
    count_until_threshold++;
    char* mem_node_as_str = mem_node_to_string(*current);
    printf("%s --> ", mem_node_as_str);
    free(mem_node_as_str);
    if (count_until_threshold == BUFFER_HORIZONTAL_THRESHOLD) {
      printf("\n");
      count_until_threshold = 0;
    }
    current = current->next;
  } 
  printf("X\n\n");
}