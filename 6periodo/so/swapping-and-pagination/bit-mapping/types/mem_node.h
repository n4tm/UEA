// Representa um nó do bloco de memória mapeado
typedef struct mem_node_t {
  struct mem_node_t* next;     // Próximo nó, para qual este nó está apontando
  char type;            // P de "processo" ou L de "livre"
  int start_index;      // Posição do trecho da memória em que esse nó inicia
  int length;           // Comprimento do nó (quantidade de bits)
  void (*to_string)();  // Para fins de amostragem
} mem_node_t;