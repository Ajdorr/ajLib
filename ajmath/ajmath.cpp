#include "ajmath.h"

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

/*
 *
 * Matrix Algorithms
 *
 */

VectorN& leastSquaresApproximation(VectorN &x,
                                  VectorN &y,
                                  unsigned int deg)
{
    unsigned int i, j;
    unsigned int dim = x.dim();
    deg++; // this is because we need an extra spot

    if (x.dim() != y.dim()) {
        // cerr << "leastSquaresApproximation: Dimensions do not match" << endl;
        return y;
    }

    Matrix mat(dim, deg);
    for (i = 0; i < dim; i++) {
        mat[i][0] = 1;
        for (j = 1; j < deg; j++) {
            mat[i][j] = mat[i][j-1]*x[i];
        }
    }

    Matrix matT(mat);
    matT.trans();

    // cout << mat << endl << endl;
    // cout << matT << endl;
    // cout << sol << endl << endl;

    y *= matT;
    // cout << sol << endl;

    (matT*mat).rref(y);

    return y;
}

