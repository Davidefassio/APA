#ifndef GCD_H
#define GCD_H

/*
 * Compute the greatest common divisor of two positive integers
 * using the euclidean algorithm.
 * Important: a > b
 */
int gcd(int a, int b){
  if(b == 0){ return(a); }
  else{ return gcd(b, a%b); }
}


#endif /* GCD_H */
