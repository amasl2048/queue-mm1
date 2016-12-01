/*arg.cpp*/
#include <math.h>

double func1(float lambda, double u) {
  return -(1 / lambda) * log(1 - u);
}

long int urn38(long int x) { // pow(5, 13)
  return (1220703125 * x) % 32768; 
}

long int urn13(long int x) { // pow(2, 32)
  return (663608941 * x) % 4294967296; 
}
