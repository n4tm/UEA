#include <math.h>
#include <time.h>

int method_exec_time(int* (*method)(long long), long long qty) {
  clock_t start_time = clock();
  method(qty);
  return clock() - start_time;
}

float chi_squared_test(int* (*method)(long long), long long qty) {
  int* occurrences = method(qty);
  float sum = 0.0;
  float expected = 0.1*qty;
  for (int i = 0; i < 10; ++i) sum += powf(occurrences[i] - expected, 2)/expected;
  return sum;
}
