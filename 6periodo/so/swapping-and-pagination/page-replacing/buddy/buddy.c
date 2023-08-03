#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MEM_SIZE 1024 // tamanho total da memória
#define MIN_SIZE 4    // tamanho mínimo de um bloco de memória (2^2)
#define MAX_LEVELS (int)(log2(MEM_SIZE/MIN_SIZE)) // máximo de níveis recursivos

// Estrutura para representar um bloco de memória
typedef struct mem_block {
  int size; // tamanho do bloco
  int free; // 1 se o bloco estiver livre, 0 caso contrário
  struct mem_block *next; // ponteiro para o próximo bloco
} mem_block_t;

// Ponteiro para o início da lista de blocos
mem_block_t *mem_start = NULL;

// Função para inicializar a lista de blocos com um bloco único de tamanho igual à MEM_SIZE
void init_mem() {
  mem_start = (mem_block_t*)malloc(sizeof(mem_block_t));
  mem_start->size = MEM_SIZE;
  mem_start->free = 1;
  mem_start->next = NULL;
}

// Função para dividir recursivamente um bloco de memória em duas partes iguais
// até encontrar um bloco livre com tamanho suficiente ou atingir o nível máximo de recursão
mem_block_t *split_block(mem_block_t *block, int size, int levels) {
  if (levels == 0) {
      return NULL;
  }

  int block_size = block->size / 2;
  if (block_size >= size && block->free) {
    mem_block_t *new_block = (mem_block_t*)malloc(sizeof(mem_block_t));
    new_block->size = block_size;
    new_block->free = 1;
    new_block->next = block->next;

    block->size = block_size;
    block->free = 0;
    block->next = new_block;

    return block;
  }

  return split_block(block->next, size, levels-1);
}

// Função para alocar um bloco de memória com tamanho igual ou superior ao especificado
void *alloc_mem(int size) {
  if (size <= 0) {
    return NULL;
  }

  // Arredonda o tamanho para a potência de 2 mais próxima
  int block_size = MIN_SIZE;
  while (block_size < size) {
    block_size *= 2;
  }

  // Procura na lista de blocos por um bloco livre com tamanho suficiente
  mem_block_t *block = mem_start;
  while (block != NULL) {
    if (block->free && block->size >= block_size) {
      // Divide recursivamente o bloco de memória, se necessário
      split_block(block, block_size, MAX_LEVELS);
      block->free = 0;
      return block + 1;
    }
    block = block->next;
  }

  // Não foi encontrado um bloco de memória livre com tamanho suficiente
  return NULL;
}

// Função para liberar um bloco de memória previamente alocado
void free_mem(void *ptr) {
  if (ptr == NULL) {
    return;
  }

  // Retorna o ponteiro para a estrutura do bloco correspondente
  mem_block_t *block = (mem_block_t*)ptr - 1;

  // Marca o bloco como livre
  block->free = 1;

  // Une o bloco com o próximo, se ambos estão livres e possuem tamanhos iguais
  while (block->next != NULL && block->next->free && block->next->size == block->size) {
    mem_block_t *next_block = block->next;
    block->next = next_block->next;
    block->size *= 2;
    free(next_block);
  }
}

// Função para imprimir o estado atual da lista de blocos
void print_mem() {
  printf("Estado atual da memoria:\n");
  mem_block_t *block = mem_start;
  while (block != NULL) {
    printf("Bloco de tamanho %d (%s)\n", block->size, block->free ? "livre" : "ocupado");
    block = block->next;
  }
  printf("\n");
}

int main() {
  // Inicializa a lista de blocos com um bloco único de tamanho MEM_SIZE
  init_mem();
  // Aloca alguns blocos de memória
  void *block1 = alloc_mem(16);
  void *block2 = alloc_mem(64);
  void *block3 = alloc_mem(128);

  // Imprime o estado atual da lista de blocos
  print_mem();

  // Libera o segundo bloco alocado
  free_mem(block2);

  // Imprime o estado atual da lista de blocos
  print_mem();

  // Tenta alocar um bloco de memória maior que o tamanho máximo disponível
  void *block4 = alloc_mem(MEM_SIZE * 2);

  // Imprime o estado atual da lista de blocos
  print_mem();

  // Libera os blocos restantes
  free_mem(block1);
  free_mem(block3);

  // Imprime o estado atual da lista de blocos
  print_mem();

  return 0;
}