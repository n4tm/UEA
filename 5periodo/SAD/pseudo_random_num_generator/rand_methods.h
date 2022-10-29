#include <time.h>

int cont;

int xorshift_method() {
  unsigned long long x = time(NULL) - cont;
  cont++; 

  x ^= (x >> 21);
  x ^= (x << 35);
  x ^= (x >> 4);

  return x;
}