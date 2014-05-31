#ifndef VECTOR3_H
#define VECTOR3_H
#include <iostream>
#include <math.h>

class Matrix3;

class Vector3
{
private:
  float v[3];

public:
  // static members
  static Vector3 Zero;
  static Vector3 One;

  Vector3() {}
  Vector3(const Vector3&);
  Vector3(float, float, float);// Construct with floating point
  Vector3& operator=(const Vector3&);// Assignment operator

  // Vector Argumented Operations
  Vector3 operator+(const Vector3&);// Component Addition
  Vector3 operator-(const Vector3&);// Component Subtraction
  Vector3 operator^(const Vector3&);// Cross Product
  float operator*(const Vector3&);// Dot Product

  // Compound Vector Argumented Operations
  Vector3& operator+=(const Vector3&);// Compound Addition
  Vector3& operator-=(const Vector3&);// Component Subtraction
  Vector3& operator^=(const Vector3&);// Compound Cross Product

  // Scalar argumented operations
  Vector3 operator*(const float);// Scalar Multiplication
  Vector3 operator/(const float);// Scalar Division

  // Compound Operations
  Vector3& operator*=(const float);// Compound Scalar Multiplication
  Vector3& operator/=(const float);// Compound Scalar Division

  // Accessor Functions
  friend std::ostream& operator<<(std::ostream&, const Vector3&);
  bool operator!=(const Vector3&);// Unequal
  bool operator==(const Vector3&);// equal
  float& operator[](int);
  float x() const;
  float y() const;
  float z() const;

  // Other Operations
  Vector3 unit();// Returns the unit vector
  void setUnit();// Returns the unit vector
  float mag(); // returns the magnitude
  float mag2(); // returns the magnitude squared

};
// Associativity operators
Vector3 operator*(const float&, const Vector3&);

// TODO indexed in column major order
class Matrix3 {
private:
  float M[9];

public:
  Matrix3(){} // simply allocates memory
  Matrix3(const float a);// creates the a * the indentity matrix
  Matrix3(const Matrix3&);// copy constructor
  // elements are assumed to be indexed in column major order
  Matrix3(const float *d); // copy from dynamic array
  // initialize with dynamic memory, must be *d[3]
  // this will only copy the first 3 elemetns of the first 3 rows
  Matrix3(const float **d); // copy from dynamic array
  Matrix3(const float d[][3]); // copy from a 3x* float array

  // Arithmetic Operators
  Matrix3& operator=(const float *d);
  Matrix3& operator=(const float **d);
  Matrix3& operator=(const float d[][3]);
  Matrix3& operator=(const float d); // equivalent to I*d, I = identity matrix
  Matrix3& operator=(const Matrix3&); // deep copy

  // Compound Arithmetic Operators
  Matrix3 operator+(const Matrix3&);// add two 3d matricies
  Matrix3 operator-(const Matrix3&);// subtract two 3d matricies
  Matrix3 operator*(const float d) const;// multiply each entry by d
  Matrix3 operator/(const float d);// multiply each entry by d
  Matrix3 operator*(const Matrix3 &A);// matrix multiplication, executed as (*this)*(A)
  Vector3 operator*(const Vector3&);// transformation matrix

  // Compound Operators
  Matrix3& operator+=(const Matrix3&);// matrix addition
  Matrix3& operator-=(const Matrix3&);// matrix subtraction
  Matrix3& operator*=(const float);// matrix multiplication
  Matrix3& operator*=(const Matrix3&);// matrix addition

  // Stream Operators
  friend std::ostream& operator<<(std::ostream&, const Matrix3&);

  // Accessor Function
  float& operator[](unsigned int);

  // Misc Operations
  void trans();
  void iden();
  void zero();
  float det();
  Matrix3 invd(); // returns det(A)*M^-1
};
Matrix3 operator*(const float&, const Matrix3&);

#endif // VECTOR3_H
