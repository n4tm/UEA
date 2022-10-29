#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "markov_chain_simulator.h"

#define M_SZ 11

void printMatrix(double matrix[M_SZ][M_SZ], const char* title) {
  printf("%s\n", title);
  for (int i = 0; i < M_SZ; ++i) {
    for (int j = 0; j < M_SZ; ++j) {
      printf("|%.3lf|", matrix[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

int main() {
  int qtd, i, j, k, rand_number;

  double a[M_SZ][M_SZ] = { 
    { 0.2,  0.1,  0.05, 0.15, 0.1,  0.05, 0.1,  0.05, 0.05, 0.1,  0.05 },
    { 0.15, 0.2,  0.1,  0.05, 0.15, 0.05, 0.05, 0.1,  0.05, 0.05, 0.05 },
    { 0.1,  0.15, 0.2,  0.05, 0.05, 0.1,  0.05, 0.05, 0.1,  0.1,  0.05 },
    { 0.1,  0.1,  0.15, 0.2,  0.1,  0.05, 0.1,  0.05, 0.05, 0.05, 0.05 },
    { 0.1,  0.1,  0.1,  0.05, 0.15, 0.1,  0.1,  0.1,  0.05, 0.1,  0.05 },
    { 0.05, 0.05, 0.1,  0.1,  0.1,  0.15, 0.1,  0.1,  0.1,  0.05, 0.1  },
    { 0.1,  0.1,  0.05, 0.05, 0.05, 0.15, 0.15, 0.15, 0.05, 0.05, 0.1  },
    { 0.05,	0.05,	0.1,	0.1,	0.05,	0.1,	0.05,	0.2,	0.15,	0.05,	0.1  },
    { 0.05,	0.1,	0.05,	0.05,	0.1,	0.05,	0.1,	0.1,	0.15,	0.15,	0.1  },
    { 0.05,	0.05,	0.1,	0.05,	0.1,	0.05,	0.15,	0.1,	0.05,	0.15,	0.15 },
    { 0.05,	0.05,	0.1,	0.05,	0.1,	0.05,	0.1,	0.05,	0.15,	0.1,	0.2  }
  }, b[M_SZ][M_SZ], c[M_SZ][M_SZ];

  memcpy(b, a, sizeof a);

  printf("Enter how many times the matrix will be multiplied: ");
  scanf("%d", &qtd);

  while (qtd--) {
    for (i = 0; i < M_SZ; ++i) {
      for (j = 0; j < M_SZ; ++j) {
        c[i][j] = 0;
        for (k = 0; k < M_SZ; ++k) {
          c[i][j] += a[i][k]*b[k][j];
        }
      }
    }
    memcpy(b, c, sizeof c);
  }

  printMatrix(b, "\nResult matrix:");
  simulateMatrix(b);
}