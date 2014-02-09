#ifndef VECTOR3_H
#define VECTOR3_H
#include <iostream>

class Matrix3;

class Vector3 {
    public:
    float x, y, z;

    Vector3();// Creates a zero vector
    Vector3(const Vector3&);
    Vector3(float, float, float);// Construct with floating point
    Vector3& operator=(const Vector3&);// Assignment operator

    // Vector Argumented Operations
    Vector3 operator+(const Vector3&);// Component Addition
    Vector3 operator-(const Vector3&);// Component Subtraction
    Vector3 operator%(const Vector3&);// Cross Product
    float operator*(const Vector3&);// Dot Product

    // Compound Vector Argumented Operations
    Vector3& operator+=(const Vector3&);// Compound Addition
    Vector3& operator-=(const Vector3&);// Component Subtraction
    Vector3& operator%=(const Vector3&);// Compound Cross Product
    Vector3& operator*=(const Matrix3&A);// executed as A*v

    // Scalar argumented operations
    Vector3 operator*(const float);// Scalar Multiplication
    Vector3 operator/(const float);// Scalar Division

    // Compound Operations
    Vector3& operator*=(const float);// Compound Scalar Multiplication
    Vector3& operator/=(const float);// Compound Scalar Division

    friend std::ostream& operator<<(std::ostream&, const Vector3&);
    bool operator!=(const Vector3&);// Unequal
    bool operator==(const Vector3&);// equal

    // Other Operations
    Vector3 Unit();// Returns the unit vector
    float Mag(); // returns the square magnitude
    void Zero(); // Sets the vector to zero
};
// Associativity operators
Vector3 operator*(const float&, const Vector3&);

// WIP
// TODO Change Name
// TODO Check if it works
class Matrix3 {
private:
    float M[3][3];

public:
    Matrix3(); // creates the identity matrix
    Matrix3(const float a);// creates the a * the indentity matrix
    Matrix3(const Matrix3&);// copy constructor
    Matrix3(float d[][3]); // copy from a 3x* float array
    Matrix3(float **d); // copy from dynamic array

    void init(float d[][3]);// initialize with static memory
    void init(float **d);// initialize with dynamic memory, must be *d[3]

    Matrix3& operator=(const float d); // assign d to every entry
    Matrix3& operator=(const Matrix3&); // deep copy
    Matrix3 operator+(const Matrix3&);// add two 3d matricies
    Matrix3 operator-(const Matrix3&);// subtract two 3d matricies
    Matrix3 operator*(const float d);// multiply each entry by d
    Matrix3 operator/(const float d);// multiply each entry by d
    Matrix3 operator*(const Matrix3 &A);// matrix multiplication, executed as (*this)*(A)
    Vector3 operator*(const Vector3&);// transformation matrix

    // Compound Operators
    Matrix3& operator+=(const Matrix3&);// matrix addition
    Matrix3& operator-=(const Matrix3&);// matrix subtraction
    Matrix3& operator*=(const float);// matrix multiplication
    Matrix3& operator*=(const Matrix3&);// matrix addition
    friend Vector3& Vector3::operator*=(const Matrix3 &A);// executed as A*v, for self matrix transformations

    // Stream Operators
    friend std::ostream& operator<<(std::ostream&, const Matrix3&);

    // Accessor Function
    float* operator[](unsigned int);

    // Misc Operations
    void trans();
    void iden();
    void zero();
    float det();
    Matrix3 inv(); // returns det(A)*M-1, done in case you already have the determinant saved
};
Matrix3 operator*(const float&, const Matrix3&);

#endif // VECTOR3_H
