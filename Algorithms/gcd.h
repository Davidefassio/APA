#ifndef GCD_H
#define GCD_H

/*
 * Compute the greatest common divisor of two positive integers
 * using the euclidean algorithm.
 * Important: a > b
 */
int gcd(int a, int b){
  if(!b) return(a);
  return gcd(b, a%b);
}

#endif /* GCD_H */
