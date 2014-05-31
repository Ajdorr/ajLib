#ifndef AJMATH_H
#define AJMATH_H
#include <math.h>
#include "sequence.h"
#include "matrix.h"
#include "matrix3.h"

#define PI 3.14159
#define DPI 6.28318
#define DEG2RAD 3.14159/180

/*
 *
 * Mathematical Namespace and Macros
 *
 *
 */

#ifndef SWAP
#define SWAP(a,b) a=a^b;b=b^a;a=a^b;
#endif

#define SWAPT(a,b,t) t=a;a=b;b=t;



/*
 *
 * Mathematical Functions
 *
 *
 */

unsigned int factorial(unsigned int);// n! functiononly does positive integers
unsigned int factorialtok(unsigned int,unsigned int);// n!/k! n > k
unsigned int nchoosek(unsigned int, unsigned int);// n choose k function

// Least Squares Approximation, takes two vectors and the degree
// approximates the equation y=Ax deg is the degree
// of the expected polynomial
// y is changed in this process, and alo returned
// x should be left unchanged
VectorN& leastSquaresApproximation(VectorN &x, VectorN &y, unsigned int deg);

#endif // AJMATH_H
