#include "libs/asprintf.h"
#include <stdio.h>

// Representa um nó do bloco de memória mapeado
typedef struct mem_node_t {
  struct mem_node_t* next;  // Próximo nó, para qual este nó está apontando
  char type;                // P de "processo" ou L de "livre"
  int start_index;          // Posição do trecho da memória em que esse nó inicia
  int length;               // Comprimento do nó (quantidade de bits)
} mem_node_t;

// Para fins de amostragem
char* mem_node_to_string(mem_node_t mem_node) {
  char* result;
  
  asprintf(&result, "[%c|%d|%d]", mem_node.type, mem_node.start_index, mem_node.length);
  return result;
}