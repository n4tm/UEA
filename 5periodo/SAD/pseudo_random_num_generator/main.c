#include <stdio.h>
#include "rand_methods.h"
#include "test_methods.h"

void test_method(struct pseudo_rand_method method) {
  for (long long i = 100000; i < 100000001LL; i *= 10) {
      printf("%lld generations:\n", i);
      printf("%s: %d ms\n", method.title, method_exec_time(method.run, i));
      printf("%s chi-squared: %f\n\n", method.title, chi_squared_test(method.run, i));
  }
}

int main() {
  /*struct pseudo_rand_method rand_method = new_rand_method();
  struct pseudo_rand_method xorshift_method = new_xorshift_method();

  test_method(rand_method);
  test_method(xorshift_method);*/
  char a[9999];
  while (scanf("%s", a) != EOF) {}

  return 0;
}