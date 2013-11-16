#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>

using namespace std;
class matrix;

class vectorn {
    private:
    double *V;
    unsigned int n;

    public:
    vectorn();// Creates the null vector
    vectorn(const vectorn&);
    vectorn(double*, unsigned int);// array and dimensions
    ~vectorn(); // destructor
    vectorn& operator=(const vectorn&);// Assignment operator

    // Vector Argumented Operations
    vectorn operator+(const vectorn&);// Component Addition
    vectorn operator-(const vectorn&);// Component Subtraction
    double operator*(const vectorn&);// Dot Product

    // Compound Vector Argumented Operations
    vectorn& operator+=(const vectorn&);// Component Addition
    vectorn& operator-=(const vectorn&);// Component Subtraction
    vectorn& operator*=(const matrix &A);// Compound Scalar Multiplication, this is executed as A*V

    // Scalar argumented operations
    vectorn operator*(const double);// Scalar Multiplication
    vectorn operator/(const double);// Scalar Division

    // Compound Operations
    vectorn& operator*=(const double);// Compound Scalar Multiplication
    vectorn& operator/=(const double);// Compound Scalar Division

    // Accessibility Operators
    double& operator[](const int);
    friend std::ostream& operator<<(std::ostream&, const vectorn&);

    unsigned int dim() const;// returns the number of entries in the vector
    vectorn unit();
    double mag();
    void zero();
};

// Global Operator
vectorn operator*(const double&, const vectorn&);

/*
 *
 * Matrix Class and Operations
 *
 */

class matrix
{
private:
    // rows then columns
    unsigned int n, m;// rows x columns; dimensions of the matrix, 0 when unitialized
    double **M; // array that actually stores the values

    void delMat();
    double zeroOnIndex(unsigned int, unsigned int, unsigned int);

public:
    matrix();// creates the NULL matrix
    matrix(const matrix &); // copy constructor
    matrix(unsigned int n,unsigned int m);// allocates a n*m matrix
    matrix(double **d, unsigned int _n,unsigned int _m);// _n is the number of the first indexs of d, _m is second indexs of d

    // creates a least common squares matrix, where n is the length of x and deg is the degree you think the relationship is
    matrix(double *x, unsigned int n, unsigned int deg);
    ~matrix();

    // initialize, done the same way as the respective constructor
    void init(double **d, unsigned int _n,unsigned int _m);// _n is the number of the first indexs of d, _m is second indexs of d

    // Arithmetic Operators
    matrix& operator=(const double); // sets the entire matrix to the passed value, uses matrix dimensions
    matrix& operator=(const matrix&); // assignment operator
    matrix operator+(const matrix&);// matrix dimensions must match, null matrix is returned if they dont
    matrix operator-();// inverts all entries in the matrix
    matrix operator-(const double); // dimension rule is applied to all operations
    matrix operator-(const matrix&);
    matrix operator*(const double);
    matrix operator*(const matrix&);// remember this is not associative
    vectorn operator*(const vectorn&);// returns the null vector if dimensions do not match

    // Compound Operators
    matrix& operator+=(const matrix&);
    matrix& operator-=(const matrix&);
    matrix& operator*=(const double);
    matrix& operator*=(const matrix&);// if the matrix dimensions do not match, the matrix is deleted
    friend vectorn& vectorn::operator*=(const matrix &A);// this is done as A*v, a little more efficient this way

    // Bitwise Operators
    friend std::ostream& operator<<(std::ostream&, const matrix&);

    // Member and Pointer Operators
    double* operator[](unsigned int i);

    // Misc Operations
    unsigned int dimr() const;// returns the dimensions of the rows
    unsigned int dimc() const;// returns the dimensions of the columns
    void trans(); // make the matrix the transpose of itself
    void iden(); // sets the matrix to the identity matrix, does not change dimensions
    void zero(); // set the matrix to the zero matrix, does not change dimensions
    double det();// calculate the determinant of the matrix, returns zero if the determinant has never been calculated
    void swpRow(unsigned int x, unsigned int y);// swaps row x with y
    void mulRow(double a, unsigned int x); // multiply row x by a
    void addLinMul(double a, unsigned int x, unsigned int y);// multiplies row x by a and adds it to row y
    void rref(); // reduces the matrix to reduced row echelon form
    void rref(vectorn&);// rref with a solution vector, vector is assumed to have the same length as rows of the matrix
    matrix inv();// returns the inverse matrix, non destructive
    // resize the matrix to rows x columns, if you do not pass a second value, it assumes you want a vector
    void resz(unsigned int, unsigned int);

};

// Global Operators
matrix operator*(const double&, const matrix&);

// Matrix Algorithms
vectorn LstSqApprox(double *X, double *Y, unsigned int n, unsigned int deg);

#endif // MATRIX_H
