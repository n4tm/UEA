#include "mem_node.h"

// Dúvida: é preciso implementar os métodos de uma linked list
// (ex: pop, remove) mesmo que não cheguem a ser utilizados?
typedef struct bitmap_linked_list_t {
  mem_node_t* head;
  void (*to_string)();
} bitmap_linked_list_t;