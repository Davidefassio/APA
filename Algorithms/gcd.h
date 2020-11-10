#ifndef GCD_H
#define GCD_H

/*
 * Compute the greatest common divisor of two positive integers
 * using the euclidean algorithm.
 * Important: a > b
 */

int gcd(int a, int b){ // Wrapper
  if(a > b) return gcdR(a, b);
  return gcdR(b, a);
}

int gcdR(int a, int b){ // Recursion
  if(!b) return(a);
  return gcd(b, a%b);
}

#endif /* GCD_H */
