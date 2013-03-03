#include "jmath.h"

/*
 *
 * Mathematical Functions
 *
 *
 */

// n! functiononly does positive integers
unsigned int factorial(unsigned int n) {
    unsigned int ret;

    ret = 1;
    for (; n > 1; n--)
        ret *= n;

    return ret;
}

// n!/k! n>k
unsigned int factorialtok(unsigned int n, unsigned int k) {
    unsigned int ret;

    ret = 1;
    for (; n > k; n--)
        ret *= n;

    return ret;

}

// n choose k function
unsigned int nchoosek(unsigned int n, unsigned int k) {
    return factorialtok(n,k)/factorial(n-k);
}
