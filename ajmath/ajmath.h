#ifndef JMATH_H
#define JMATH_H
#include <math.h>
#include "sequence.h"
#include "matrix.h"
#include "matrix3.h"

#define PI 3.14159
#define DEG2RAD 3.14159/180

/*
 *
 * Mathematical Namespace and Macros
 *
 *
 */

namespace ajMath {
    static Vector3 Zero = Vector3(0.0, 0.0, 0.0);
    static Vector3 One = Vector3(1.0, 1.0, 1.0);
}

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
// Linear Reduction
VectorN leastSquaresApproximation(const VectorN &x, const VectorN &y);

#endif // JMATH_H
