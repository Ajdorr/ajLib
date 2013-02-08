#ifndef JMATH_H
#define JMATH_H
#include <math.h>
#include "sequence.h"
#include "matrix.h"
#include "matrix3.h"

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
unsigned int factorialtok(unsigned int,unsigned int);// n!/k!
unsigned int nchoosek(unsigned int, unsigned int);// n choose k function

#endif // JMATH_H
