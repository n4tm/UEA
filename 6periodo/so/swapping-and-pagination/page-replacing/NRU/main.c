#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define MAX_PROCESSES 10
#define MAX_PAGES 10

// Estrutura que representa uma página na memória
typedef struct {
  int page_number;    // Número da página
  int R_bit;          // Bit R
  int M_bit;          // Bit M
} page_t;

// Função que inicializa as páginas de um processo
void init_process_pages(page_t pages[], int num_pages) {
  int i;
  for (i = 0; i < num_pages; i++) {
    pages[i].page_number = i;
    pages[i].R_bit = rand() % 2;
    pages[i].M_bit = rand() % 2;
  }
}

// Função que simula o acesso a uma página
void access_page(page_t *page) {
  // Acessa a página
  printf("Acessando página %d...\n", page->page_number);

  // Atualiza o bit R
  page->R_bit = 1;

  // Atualiza o bit M
  if (rand() % 2 == 0) {
    page->M_bit = 1;
  }
}

// Função que escolhe uma página para substituição, utilizando o algoritmo NRU
int choose_page_to_replace(page_t pages[], int num_pages) {
  int i, j;
  int class[4] = {0, 0, 0, 0};  // Classe 0: R=0, M=0; Classe 1: R=0, M=1; Classe 2: R=1, M=0; Classe 3: R=1, M=1

  // Classifica as páginas em suas respectivas classes
  for (i = 0; i < num_pages; i++) {
    if (pages[i].R_bit == 0 && pages[i].M_bit == 0) {
      class[0]++;
    } else if (pages[i].R_bit == 0 && pages[i].M_bit == 1) {
      class[1]++;
    } else if (pages[i].R_bit == 1 && pages[i].M_bit == 0) {
      class[2]++;
    } else {
      class[3]++;
    }
  }

  // Escolhe uma página aleatória da classe menos restritiva
  for (i = 0; i < 4; i++) {
    if (class[i] > 0) {
      int pages_in_class[class[i]];
      j = 0;
      for (int k = 0; k < num_pages; k++) {
        if ((pages[k].R_bit == 0 && pages[k].M_bit == 0 && i == 0) ||
          (pages[k].R_bit == 0 && pages[k].M_bit == 1 && i == 1) ||
          (pages[k].R_bit == 1 && pages[k].M_bit == 0 && i == 2) ||
          (pages[k].R_bit == 1 && pages[k].M_bit == 1 && i == 3)) {
          pages_in_class[j] = k;
          j++;
        }
      }
      return pages_in_class[rand() % class[i]];
    }
  }

  return -1;  // Não há páginas na memória
}

// Função principal
int main() {
  srand(time(NULL)); // Inicializa o gerador de números aleatórios com o valor atual do relógio
  page_t pages[MAX_PAGES];  // Array de páginas na memória
  int num_processes = rand() % MAX_PROCESSES + 1;  // Número de processos (entre 1 e MAX_PROCESSES)
  int i, j;

  // Cria os processos fake e inicializa suas páginas
  for (i = 0; i < num_processes; i++) {
    printf("Processo %d:\n", i);
    int num_pages = rand() % MAX_PAGES + 1;  // Número de páginas do processo (entre 1 e MAX_PAGES)
    page_t process_pages[num_pages];  // Páginas do processo

    // Inicializa as páginas do processo
    init_process_pages(process_pages, num_pages);

    // Copia as páginas do processo para o array de páginas na memória
    for (j = 0; j < num_pages; j++) {
      pages[i * MAX_PAGES + j] = process_pages[j];
    }
  }

  // Simula o acesso aleatório a páginas
  int num_accesses = rand() % (num_processes * MAX_PAGES) + 1;  // Número de acessos (entre 1 e num_processes * MAX_PAGES)
  for (i = 0; i < num_accesses; i++) {
    int page_index = rand() % (num_processes * MAX_PAGES);  // Índice aleatório da página na memória
    access_page(&pages[page_index]);
  }

  // Escolhe uma página para substituição utilizando o algoritmo NRU
  int page_to_replace_index = choose_page_to_replace(pages, num_processes * MAX_PAGES);

  // Exibe o resultado da escolha
  if (page_to_replace_index == -1) {
    printf("Não há páginas na memória para substituição.\n");
  } else {
    printf("Página %d foi escolhida para substituição.\n", page_to_replace_index);
  }

  return 0;
}