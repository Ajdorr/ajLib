#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>

// type of input that the
#define MATRIX_TYPE float

using namespace std;
class Matrix;

class VectorN {
    private:
    MATRIX_TYPE *V;
    unsigned int n;

    public:
    VectorN();// Creates the null vector
    VectorN(const VectorN&);
    VectorN(unsigned int);// array and dimensions
    VectorN(MATRIX_TYPE*, unsigned int);// array and dimensions
    VectorN& operator=(const VectorN&);// Assignment operator
    ~VectorN(); // destructor

    // Vector Argumented Operations
    VectorN operator+(const VectorN&);// Component Addition
    VectorN operator-(const VectorN&);// Component Subtraction
    MATRIX_TYPE operator*(const VectorN&);// Dot Product

    // Compound Vector Argumented Operations
    VectorN& operator+=(const VectorN&);// Component Addition
    VectorN& operator-=(const VectorN&);// Component Subtraction
    // Compound Scalar Multiplication, this is executed as A*V
    VectorN& operator*=(const Matrix &A);

    // Scalar argumented operations
    VectorN operator*(const MATRIX_TYPE);// Scalar Multiplication
    VectorN operator/(const MATRIX_TYPE);// Scalar Division

    // Compound Operations
    VectorN& operator*=(const MATRIX_TYPE);// Compound Scalar Multiplication
    VectorN& operator/=(const MATRIX_TYPE);// Compound Scalar Division

    // Accessibility Operators
    MATRIX_TYPE& operator[](const int);
    friend std::ostream& operator<<(std::ostream&, const VectorN&);

    unsigned int dim() const;// returns the number of entries in the vector
    VectorN unit();
    MATRIX_TYPE mag();
    void zero();
};

// Global Operator
VectorN operator*(const MATRIX_TYPE&, const VectorN&);

/*
 *
 * Matrix Class and Operations
 *
 */

class Matrix
{
private:
    // rows then columns
    unsigned int n, m;// rows x columns; dimensions of the Matrix, 0 when unitialized
    MATRIX_TYPE **M; // array that actually stores the values

    void delMat();
    MATRIX_TYPE zeroOnIndex(unsigned int, unsigned int, unsigned int);

public:
    Matrix();// creates the NULL Matrix
    Matrix(const Matrix &); // copy constructor
    Matrix(unsigned int a); // allocates an a*a matrix
    Matrix(unsigned int a, unsigned int b);// allocates a a*b Matrix
    Matrix(MATRIX_TYPE **d, unsigned int _n, unsigned int _m);
    ~Matrix();

    // initialize, done the same way as the respective constructor
    void init(MATRIX_TYPE **d, unsigned int _n,unsigned int _m);// _n is the number of the first indexs of d, _m is second indexs of d

    // Arithmetic Operators
    Matrix& operator=(const MATRIX_TYPE); // sets the entire Matrix to the passed value, uses Matrix dimensions
    Matrix& operator=(const Matrix&); // assignment operator
    Matrix operator+(const Matrix&);// Matrix dimensions must match, null Matrix is returned if they dont
    Matrix operator-();// inverts all entries in the Matrix
    Matrix operator-(const MATRIX_TYPE); // dimension rule is applied to all operations
    Matrix operator-(const Matrix&);
    Matrix operator*(const MATRIX_TYPE);
    Matrix operator*(const Matrix&);// remember this is not associative
    VectorN operator*(const VectorN&);// returns the null vector if dimensions do not match

    // Compound Operators
    Matrix& operator+=(const Matrix&);
    Matrix& operator-=(const Matrix&);
    Matrix& operator*=(const MATRIX_TYPE);
    Matrix& operator*=(const Matrix&);// if the Matrix dimensions do not match, the Matrix is deleted
    friend VectorN& VectorN::operator*=(const Matrix &A);// this is done as A*v, a little more efficient this way

    // Bitwise Operators
    friend std::ostream& operator<<(std::ostream&, const Matrix&);

    // Member and Pointer Operators
    MATRIX_TYPE* operator[](unsigned int i);

    // Misc Operations
    unsigned int dimr() const;// returns the dimensions of the rows
    unsigned int dimc() const;// returns the dimensions of the columns
    void trans(); // make the Matrix the transpose of itself
    void iden(); // sets the Matrix to the identity Matrix, does not change dimensions
    void zero(); // set the Matrix to the zero Matrix, does not change dimensions
    MATRIX_TYPE det();// calculate the determinant of the Matrix, returns zero if the determinant has never been calculated
    void swpRow(unsigned int x, unsigned int y);// swaps row x with y
    void mulRow(MATRIX_TYPE a, unsigned int x); // multiply row x by a
    void addLinMul(MATRIX_TYPE a, unsigned int x, unsigned int y);// multiplies row x by a and adds it to row y
    void rref(); // reduces the Matrix to reduced row echelon form
    void rref(VectorN&);// rref with a solution vector, vector is assumed to have the same length as rows of the Matrix
    Matrix inv();// returns the inverse Matrix, non destructive
    // resize the Matrix to rows x columns, if you do not pass a second value, it assumes you want a vector
    void resz(unsigned int, unsigned int);

};

// Global Operators
Matrix operator*(const MATRIX_TYPE&, const Matrix&);

#endif // MATRIX_H
