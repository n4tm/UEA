#include "../pseudo_random_num_generator/rand_methods.h"

#define MONTHS_QTY 6
#define M_SZ 11

int states[M_SZ] = { 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35 };

int next_value(int rand_num, const double *a) {
  if (rand_num < 0) rand_num *= -1;
  rand_num %= 100;

  for (int i = 0; i < M_SZ; ++i) {
    double sum = 0;
    for (int j = 0; j < i+1; ++j) sum += a[j];
    if (rand_num < sum*100) return states[i];
  }
  return states[M_SZ-1];
}

void simulateMatrix(double m[M_SZ][M_SZ]) {
  int current_state = states[0];
  int months[MONTHS_QTY];
  for (int i = 0; i < MONTHS_QTY; ++i) {
    current_state = next_value(xorshift_method(), m[current_state-25]);
    months[i] = current_state;
  }

  for (int i = 0; i < MONTHS_QTY; ++i) printf("Mes [%d]: %d\n", i+1, states[months[i]-25]);
}