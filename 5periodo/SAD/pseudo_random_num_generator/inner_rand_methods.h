#include <stdlib.h>
#include <time.h>

int* rand_method(long long qty) {
  srand((unsigned)time(NULL));
  static int occurrences[10];
  for (int i = 0; i < 10; ++i) occurrences[i] = 0;

  while(qty--) occurrences[rand() % 10]++;

  return occurrences;
}

int xorshift_method(int lower_limit, int upper_limit) {
  unsigned long long x = time(NULL);

  while (qty--) {
    x ^= (x >> 21);
    x ^= (x << 35);
    x ^= (x >> 4);
  }
  x %= upper_limit;
  if (x < lower_limit) x += lower_limit;
  return x;
}