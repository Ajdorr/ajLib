#ifndef MATRIX4_H
#define MATRIX4_H
#include <iostream>
#include <math.h>

#include "matrix3.h"

class Vector4
{
private:
public:
  float v[4];

  static Vector4 One;
  static Vector4 Zero;

  Vector4() {}
  Vector4(const Vector4&);
  Vector4(const Vector3&);
  // Construct with floating point
  Vector4(const float, const float, const float, const float);
  Vector4& operator=(const Vector4&);// Assignment operator

  // Vector Argumented Operations
  Vector4 operator+(const Vector4&);// Addition
  Vector4 operator-(const Vector4&);// Subtraction
  float operator*(const Vector4&);// Dot Product

  // Compound Vector Argumented Operations
  Vector4& operator+=(const Vector4&);// Compound Addition
  Vector4& operator-=(const Vector4&);// Component Subtraction

  // Scalar argumented operations
  Vector4 operator*(const float);// Scalar Multiplication
  Vector4 operator/(const float);// Scalar Division

  // Compound Operations
  Vector4& operator*=(const float);// Compound Scalar Multiplication
  Vector4& operator/=(const float);// Compound Scalar Division

  friend std::ostream& operator<<(std::ostream&, const Vector4&);
  bool operator!=(const Vector4&);// Unequal
  bool operator==(const Vector4&);// equal
  float& operator[](int);
  float x() const { return v[0]; }
  float y() const { return v[1]; }
  float z() const { return v[2]; }
  float w() const { return v[4]; }

  // Other Operations
  Vector4 unit();// Returns the unit vector
  void setUnit();// divides the vector by the magnitude
  float mag(); // returns the square magnitude
  float mag2(); // returns the magnitude squared
};

Vector4 operator*(const float&, const Vector4&);

// TODO
class Quaternion
{
};

// Designed to be used with opengl
// therefore this is a column major saved matrix
// TODO Test this
class Matrix4
{
private:
  float M[16];
public:
  Matrix4() {}
  Matrix4(const float a);// creates the a * the indentity matrix
  Matrix4(const Matrix4&);// copy constructor
  Matrix4(float *d); // copy from dynamic array
  Matrix4(float **d); // copy from dynamic array
  Matrix4(float d[][4]); // copy from a 3x* float array
  Matrix4(const Vector3&, const Vector3&, const Vector3&, const Vector3&);
  Matrix4(const Vector4&, const Vector4&, const Vector4&, const Vector4&);

  Matrix4& operator=(float d[][4]);// initialize with static memory
  Matrix4& operator=(float **d);// initialize with dynamic memory, must be *d[4]
  Matrix4& operator=(float *d);// initialize with dynamic memory, must be *d[4]
  Matrix4& operator=(const float d); // equivalent to I*d, I = identity matrix
  Matrix4& operator=(const Matrix4&); // deep copy

  Matrix4 operator+(const Matrix4&);// add two 3d matricies
  Matrix4 operator-(const Matrix4&);// subtract two 3d matricies
  Matrix4 operator*(const float d) const;// multiply each entry by d
  Matrix4 operator/(const float d);// multiply each entry by d
  Matrix4 operator*(const Matrix4 &A);// matrix multiplication, executed as (*this)*(A)

  // last dim is set to 0 and multiplied as if its a 4 dim vector
  Vector4 operator*(const Vector3&); // Matrix multiplied by a 3 dim vector
  Vector4 operator*(const Vector4&); // Matrix multiplied by a 4 dim vector

  // Compound Operators
  Matrix4& operator+=(const Matrix4&);// matrix addition
  Matrix4& operator-=(const Matrix4&);// matrix subtraction
  Matrix4& operator*=(const float);// matrix multiplication
  Matrix4& operator*=(const Matrix4&);// matrix addition

  // Stream Operators
  friend std::ostream& operator<<(std::ostream&, const Matrix4&);

  // Accessor Function
  float& operator[](unsigned int);

  // Misc Operations
  void trans();
  void iden();
  void zero();
  float det();
  Matrix4 invd(); // returns the det(M)*M^-1
};

Matrix3 operator*(const float&, const Matrix3&);

#endif // MATRIX4_H
