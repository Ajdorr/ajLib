#ifndef VECTOR3_H
#define VECTOR3_H
#include <iostream>

class matrix3;
class vector3 {
    public:
    double x, y, z;
    vector3();// Creates a zero vector
    vector3(const vector3&);
    vector3(double, double, double);// Construct with floating point
    vector3& operator=(const vector3&);// Assignment operator

    // Vector Argumented Operations
    vector3 operator+(const vector3&);// Component Addition
    vector3 operator-(const vector3&);// Component Subtraction
    vector3 operator%(const vector3&);// Cross Product
    double operator*(const vector3&);// Dot Product

    // Compound Vector Argumented Operations
    vector3& operator+=(const vector3&);// Compound Addition
    vector3& operator-=(const vector3&);// Component Subtraction
    vector3& operator%=(const vector3&);// Compound Cross Product
    vector3& operator*=(const matrix3&A);// executed as A*v

    // Scalar argumented operations
    vector3 operator*(const double);// Scalar Multiplication
    vector3 operator/(const double);// Scalar Division

    // Compound Operations
    vector3& operator*=(const double);// Compound Scalar Multiplication
    vector3& operator/=(const double);// Compound Scalar Division

    friend std::ostream& operator<<(std::ostream&, const vector3&);
    bool operator!=(const vector3&);// Unequal
    bool operator==(const vector3&);// equal

    // Other Operations
    vector3 Unit();// Returns the unit vector
    double Mag(); // returns the square magnitude
    void Zero(); // Sets the vector to zero
};

// Associativity operators
vector3 operator*(const double&, const vector3&);

// WIP
class matrix3 {
    private:
    double M[3][3];

    public:
    matrix3(); // creates the identity matrix
    matrix3(const double a);// creates the a * the indentity matrix
    matrix3(const matrix3&);// copy constructor
    matrix3(double d[][3]); // copy from a 3x* double array
    matrix3(double **d); // copy from dynamic array

    void init(double d[][3]);// initialize with static memory
    void init(double **d);// initialize with dynamic memory, must be *d[3]

    matrix3& operator=(const double d); // assign d to every entry
    matrix3& operator=(const matrix3&); // deep copy
    matrix3 operator+(const matrix3&);// add two 3d matricies
    matrix3 operator-(const matrix3&);// subtract two 3d matricies
    matrix3 operator*(const double d);// multiply each entry by d
    matrix3 operator/(const double d);// multiply each entry by d
    matrix3 operator*(const matrix3 &A);// matrix multiplication, executed as (*this)*(A)
    vector3 operator*(const vector3&);// transformation matrix

    // Compound Operators
    matrix3& operator+=(const matrix3&);// matrix addition
    matrix3& operator-=(const matrix3&);// matrix subtraction
    matrix3& operator*=(const double);// matrix multiplication
    matrix3& operator*=(const matrix3&);// matrix addition
    friend vector3& vector3::operator*=(const matrix3 &A);// executed as A*v, for self matrix transformations

    // Stream Operators
    friend std::ostream& operator<<(std::ostream&, const matrix3&);

    // Accessor Function
    double* operator[](unsigned int);

    // Misc Operations
    void trans();
    void iden();
    void zero();
    double det();
    matrix3 inv(); // returns det(A)*M-1, done in case you already have the determinant saved
};

matrix3 operator*(const double&, const matrix3&);

#endif // VECTOR3_H
