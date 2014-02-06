#include <iostream>
#include "matrix4.h"

Matrix4::Matrix4()
{
}

Matrix4::Matrix4(const double a)
{
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (i == j) M[j][i] = a;
            else M[j][i] = 0;
        }
    }

}


Matrix4::Matrix4(const Matrix4 &A)
{
    for (unsigned int i= 0; i < 4; i++) {
        for (unsigned int j= 0; j < 4; j++) {
            M[i][j] = A.M[i][j];
        }
    }
}


Matrix4::Matrix4(double d[][4])
{
    for (unsigned int i= 0; i < 4; i++) {
        for (unsigned int j= 0; j < 4; j++) {
            M[i][j] = d[i][j];
        }
    }
}


Matrix4::Matrix4(double **d){
    for (unsigned int i= 0; i < 4; i++) {
        for (unsigned int j= 0; j < 4; j++) {
            M[i][j] = d[i][j];
        }
    }

}

void Matrix4::init(double d[][4]){
    for (unsigned int i= 0; i < 4; i++) {
        for (unsigned int j= 0; j < 4; j++) {
            M[i][j] = d[i][j];
        }
    }
}

void Matrix4::init(double **d)
{
    for (unsigned int i= 0; i < 4; i++) {
        for (unsigned int j= 0; j < 4; j++) {
            M[i][j] = d[i][j];
        }
    }
}

Matrix4& Matrix4::operator=(const double d)
{
    for (unsigned int i= 0; i < 3; i++) {
        for (unsigned int j= 0; j < 4; j++) {
            M[i][j] = d;
        }
    }
    return *this;
}

Matrix4& Matrix4::operator=(const Matrix4 &A)
{
    if (&A == this)
        return *this;
    for (unsigned int i= 0; i < 3; i++) {
        for (unsigned int j= 0; j < 3; j++) {
            M[i][j] = A.M[i][j];
        }
    }
    return *this;
}
/*
Matrix4 Matrix4::operator+(const Matrix4&);// add two 3d matricies
Matrix4 Matrix4::operator-(const Matrix4&);// subtract two 3d matricies
Matrix4 Matrix4::operator*(const double d);// multiply each entry by d
Matrix4 Matrix4::operator/(const double d);// multiply each entry by d
Matrix4 Matrix4::operator*(const Matrix4 &A);// matrix multiplication, executed as (*this)*(A)

// Compound Operators
Matrix4& Matrix4::operator+=(const Matrix4&);// matrix addition
Matrix4& Matrix4::operator-=(const Matrix4&);// matrix subtraction
Matrix4& Matrix4::operator*=(const double);// matrix multiplication
Matrix4& Matrix4::operator*=(const Matrix4&);// matrix addition

// Stream Operators
friend std::ostream& operator<<(std::ostream&, const Matrix4&);

// Accessor Function
double* Matrix4::operator[](unsigned int);

// Misc Operations
void Matrix4::trans();
void Matrix4::iden();
void Matrix4::zero();
double Matrix4::det();
Matrix4 Matrix4::inv();
*/
