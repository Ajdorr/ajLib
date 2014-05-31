#include "matrix4.h"

Vector4 Vector4::One = Vector4(1, 1, 1, 1);
Vector4 Vector4::Zero = Vector4(0, 0, 0, 0);

Vector4::Vector4(const Vector4& other)
{
  v[0] = other.v[0];
  v[1] = other.v[1];
  v[2] = other.v[2];
  v[3] = other.v[3];
}

Vector4::Vector4(const Vector3& other)
{
  v[0] = other.x();
  v[1] = other.y();
  v[2] = other.z();
  v[3] = 0;
}

Vector4::Vector4(const float a, const float b, const float c, const float d)
{
  v[0] = a;
  v[1] = b;
  v[2] = c;
  v[3] = d;
}

Vector4& Vector4::operator=(const Vector4& other)
{
  v[0] = other.v[0];
  v[1] = other.v[1];
  v[2] = other.v[2];
  v[3] = other.v[3];

  return *this;
}

// Vector Argumented Operations
Vector4 Vector4::operator+(const Vector4& other)
{
  Vector4 ret;

  ret.v[0] = v[0] + other.v[0];
  ret.v[1] = v[1] + other.v[1];
  ret.v[2] = v[2] + other.v[2];
  ret.v[3] = v[3] + other.v[3];

  return ret;
}

Vector4 Vector4::operator-(const Vector4& other)
{
  Vector4 ret;

  ret.v[0] = v[0] - other.v[0];
  ret.v[1] = v[1] - other.v[1];
  ret.v[2] = v[2] - other.v[2];
  ret.v[3] = v[3] - other.v[3];

  return ret;
}

float Vector4::operator*(const Vector4& other)
{
  return v[0] * other.v[0] +
      v[1] * other.v[1] +
      v[2] * other.v[2] +
      v[3] * other.v[3];
}

// Compound Vector Argumented Operations
Vector4& Vector4::operator+=(const Vector4& other)
{
  v[0] += other.v[0];
  v[1] += other.v[1];
  v[2] += other.v[2];
  v[3] += other.v[3];

  return *this;
}

Vector4& Vector4::operator-=(const Vector4& other)
{
  v[0] -= other.v[0];
  v[1] -= other.v[1];
  v[2] -= other.v[2];
  v[3] -= other.v[3];

  return *this;
}

// Scalar argumented operations
Vector4 Vector4::operator*(const float a)
{
  Vector4 ret;

  ret.v[0] = v[0]*a;
  ret.v[1] = v[1]*a;
  ret.v[2] = v[2]*a;
  ret.v[3] = v[3]*a;

  return ret;
}

Vector4 Vector4::operator/(const float a)
{
  Vector4 ret;

  ret.v[0] = v[0]/a;
  ret.v[1] = v[1]/a;
  ret.v[2] = v[2]/a;
  ret.v[3] = v[3]/a;

  return ret;
}

// Compound Operations
Vector4& Vector4::operator*=(const float a)
{
  v[0] *= a;
  v[1] *= a;
  v[2] *= a;
  v[3] *= a;

  return *this;
}

Vector4& Vector4::operator/=(const float d)
{
  v[0] /= d;
  v[1] /= d;
  v[2] /= d;
  v[3] /= d;

  return *this;
}

std::ostream& operator<<(std::ostream& os, const Vector4& vec)
{
  os << "<" << vec.v[0] << ", " << vec.v[1] << ", "
     << vec.v[2] << ", " << vec.v[3] << ">";
  return os;
}

bool Vector4::operator!=(const Vector4& other)
{
  return (other.v[0] != v[0]) ||
      (other.v[1] != v[1]) ||
      (other.v[2] != v[2]) ||
      (other.v[3] != v[3]);
}

bool Vector4::operator==(const Vector4& other)
{
  return (other.v[0] == v[0]) &&
      (other.v[1] == v[1]) &&
      (other.v[2] == v[2]) &&
      (other.v[3] == v[3]);
}

float& Vector4::operator[](int i)
{
  return v[i];
}

// Other Operations
Vector4 Vector4::unit()
{
  Vector4 ret;
  float a = this->mag();
  if (a==0) return ret;
  a = 1/a;

  ret.v[0] = v[0]*a;
  ret.v[1] = v[1]*a;
  ret.v[2] = v[2]*a;
  ret.v[3] = v[3]*a;

  return ret;
}

void Vector4::setUnit()
{
  float a = this->mag();
  if (a != 0)
  {
    a = 1/a;

    v[0] *= a;
    v[1] *= a;
    v[2] *= a;
    v[3] *= a;
  }
}

float Vector4::mag()
{
  return sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2] + v[3]*v[3]);
}
float Vector4::mag2()
{
  return v[0]*v[0] + v[1]*v[1] + v[2]*v[2] + v[3]*v[3];
}


Vector4 operator*(const float& f, const Vector4& vec)
{
  Vector4 ret(f*vec.v[0], f*vec.v[1], f*vec.v[2], f*vec.v[3]);

  return ret;
}

/*
 *
 * 4x4 square matrix
 *
 */

Matrix4::Matrix4(const float a)
{
  M[0] = a; M[1] = 0; M[2] = 0; M[3] = 0;
  M[4] = 0; M[5] = a; M[6] = 0; M[7] = 0;
  M[8] = 0; M[9] = 0; M[10] = a; M[11] = 0;
  M[12] = 0; M[13] = 0; M[14] = 0; M[15] = a;
}



Matrix4::Matrix4(const Matrix4 &A)
{
  M[0] = A.M[0]; M[1] = A.M[1]; M[2] = A.M[2]; M[3] = A.M[3];
  M[4] = A.M[4]; M[5] = A.M[5]; M[6] = A.M[6]; M[7] = A.M[7];
  M[8] = A.M[8]; M[9] = A.M[9]; M[10] = A.M[10]; M[11] = A.M[11];
  M[12] = A.M[12]; M[13] = A.M[13]; M[14] = A.M[14]; M[15] = A.M[15];
}



Matrix4::Matrix4(float **d){
  for (unsigned int j= 0; j < 4; j++) {
    M[4*j] = d[j][0];
    M[4*j + 1] = d[j][1];
    M[4*j + 2] = d[j][2];
    M[4*j + 3] = d[j][3];
  }
}

Matrix4::Matrix4(float *d)
{
  M[0] = d[0]; M[1] = d[1]; M[2] = d[2]; M[3] = d[3];
  M[4] = d[4]; M[5] = d[5]; M[6] = d[6]; M[7] = d[7];
  M[8] = d[8]; M[9] = d[9]; M[10] = d[10]; M[11] = d[11];
  M[12] = d[12]; M[13] = d[13]; M[14] = d[14]; M[15] = d[15];
}


Matrix4::Matrix4(const Vector3& v0, const Vector3& v1,
                 const Vector3& v2, const Vector3& v3)
{
  M[0] = v0.x(); M[1] = v0.y(); M[2] = v0.z(); M[3] = 0;
  M[4] = v1.x(); M[5] = v1.y(); M[6] = v1.z(); M[7] = 0;
  M[8] = v2.x(); M[9] = v2.y(); M[10] = v2.z(); M[11] = 0;
  M[12] = v3.x(); M[13] = v3.y(); M[14] = v3.z(); M[15] = 0;
}

Matrix4::Matrix4(const Vector4& v0, const Vector4& v1,
                 const Vector4& v2, const Vector4& v3)
{
  M[0] = v0.x(); M[1] = v0.y(); M[2] = v0.z(); M[3] = v0.w();
  M[4] = v1.x(); M[5] = v1.y(); M[6] = v1.z(); M[7] = v1.w();
  M[8] = v2.x(); M[9] = v2.y(); M[10] = v2.z(); M[11] = v2.w();
  M[12] = v3.x(); M[13] = v3.y(); M[14] = v3.z(); M[15] = v3.w();
}

Matrix4& Matrix4::operator=(float d[][4]){
  M[0] = d[0][0]; M[1] = d[0][1]; M[2] = d[0][2]; M[3] = d[0][3];
  M[4] = d[1][0]; M[5] = d[1][1]; M[6] = d[1][2]; M[7] = d[1][3];
  M[8] = d[2][0]; M[9] = d[2][1]; M[10] = d[2][2]; M[11] = d[2][3];
  M[12] = d[3][0]; M[13] = d[3][1]; M[14] = d[3][2]; M[15] = d[3][3];

  return *this;
}

Matrix4& Matrix4::operator=(float **d)
{
  M[0] = d[0][0]; M[1] = d[0][1]; M[2] = d[0][2]; M[3] = d[0][3];
  M[4] = d[1][0]; M[5] = d[1][1]; M[6] = d[1][2]; M[7] = d[1][3];
  M[8] = d[2][0]; M[9] = d[2][1]; M[10] = d[2][2]; M[11] = d[2][3];
  M[12] = d[3][0]; M[13] = d[3][1]; M[14] = d[3][2]; M[15] = d[3][3];

  return *this;
}

Matrix4& Matrix4::operator=(const float d)
{
  M[0] = d; M[1] = 0; M[2] = 0; M[3] = 0;
  M[4] = 0; M[5] = d; M[6] = 0; M[7] = 0;
  M[8] = 0; M[9] = 0; M[10] = d; M[11] = 0;
  M[12] = 0; M[13] = 0; M[14] = 0; M[15] = d;

  return *this;
}

Matrix4& Matrix4::operator=(const Matrix4 &A)
{
  if (&A == this)
    return *this;
  for (unsigned int i= 0; i < 4; i++) {
    M[4*i] = A.M[4*i];
    M[4*i + 1] = A.M[4*i + 1];
    M[4*i + 2] = A.M[4*i + 2];
    M[4*i + 3] = A.M[4*i + 3];
  }
  return *this;
}

Matrix4 Matrix4::operator+(const Matrix4& A)
{
  Matrix4 ret;

  ret.M[0] = M[0] + A.M[0];
  ret.M[1] = M[1] + A.M[1];
  ret.M[2] = M[2] + A.M[2];
  ret.M[3] = M[3] + A.M[3];

  ret.M[4] = M[4] + A.M[4];
  ret.M[5] = M[5] + A.M[5];
  ret.M[6] = M[6] + A.M[6];
  ret.M[7] = M[7] + A.M[7];

  ret.M[8] = M[8] + A.M[8];
  ret.M[9] = M[9] + A.M[9];
  ret.M[10] = M[10] + A.M[10];
  ret.M[11] = M[11] + A.M[11];

  ret.M[12] = M[12] + A.M[12];
  ret.M[13] = M[13] + A.M[13];
  ret.M[14] = M[14] + A.M[14];
  ret.M[15] = M[15] + A.M[15];

  return ret;

}

Matrix4 Matrix4::operator-(const Matrix4& A)
{
  Matrix4 ret;

  ret.M[0] = M[0] - A.M[0];
  ret.M[1] = M[1] - A.M[1];
  ret.M[2] = M[2] - A.M[2];
  ret.M[3] = M[3] - A.M[3];

  ret.M[4] = M[4] - A.M[4];
  ret.M[5] = M[5] - A.M[5];
  ret.M[6] = M[6] - A.M[6];
  ret.M[7] = M[7] - A.M[7];

  ret.M[8] = M[8] - A.M[8];
  ret.M[9] = M[9] - A.M[9];
  ret.M[10] = M[10] - A.M[10];
  ret.M[11] = M[11] - A.M[11];

  ret.M[12] = M[12] - A.M[12];
  ret.M[13] = M[13] - A.M[13];
  ret.M[14] = M[14] - A.M[14];
  ret.M[15] = M[15] - A.M[15];

  return ret;

}

Matrix4 Matrix4::operator*(const float d) const
{
  Matrix4 ret;

  ret.M[0] = d*M[0];
  ret.M[1] = d*M[1];
  ret.M[2] = d*M[2];
  ret.M[3] = d*M[3];

  ret.M[4] = d*M[4];
  ret.M[5] = d*M[5];
  ret.M[6] = d*M[6];
  ret.M[7] = d*M[7];

  ret.M[8] = d*M[8];
  ret.M[9] = d*M[9];
  ret.M[10] = d*M[10];
  ret.M[11] = d*M[11];

  ret.M[12] = d*M[12];
  ret.M[13] = d*M[13];
  ret.M[14] = d*M[14];
  ret.M[15] = d*M[15];

  return ret;

}

Matrix4 Matrix4::operator/(const float a)
{
  Matrix4 ret;
  float d = 1/a;

  ret.M[0] = d*M[0];
  ret.M[1] = d*M[1];
  ret.M[2] = d*M[2];
  ret.M[3] = d*M[3];

  ret.M[4] = d*M[4];
  ret.M[5] = d*M[5];
  ret.M[6] = d*M[6];
  ret.M[7] = d*M[7];

  ret.M[8] = d*M[8];
  ret.M[9] = d*M[9];
  ret.M[10] = d*M[10];
  ret.M[11] = d*M[11];

  ret.M[12] = d*M[12];
  ret.M[13] = d*M[13];
  ret.M[14] = d*M[14];
  ret.M[15] = d*M[15];

  return ret;

}

Matrix4 Matrix4::operator*(const Matrix4 &A)
{
  Matrix4 ret;

  ret.M[0] = M[0]*A.M[0] + M[4]*A.M[1] + M[8]*A.M[2] + M[12]*A.M[3];
  ret.M[1] = M[1]*A.M[0] + M[5]*A.M[1] + M[9]*A.M[2] + M[13]*A.M[3];
  ret.M[2] = M[2]*A.M[0] + M[6]*A.M[1] + M[10]*A.M[2] + M[14]*A.M[3];
  ret.M[3] = M[3]*A.M[0] + M[7]*A.M[1] + M[11]*A.M[2] + M[15]*A.M[3];

  ret.M[4] = M[0]*A.M[4] + M[4]*A.M[5] + M[8]*A.M[6] + M[12]*A.M[7];
  ret.M[5] = M[1]*A.M[4] + M[5]*A.M[5] + M[9]*A.M[6] + M[13]*A.M[7];
  ret.M[6] = M[2]*A.M[4] + M[6]*A.M[5] + M[10]*A.M[6] + M[14]*A.M[7];
  ret.M[7] = M[3]*A.M[4] + M[7]*A.M[5] + M[11]*A.M[6] + M[15]*A.M[7];

  ret.M[8] = M[0]*A.M[8] + M[4]*A.M[9] + M[8]*A.M[10] + M[12]*A.M[11];
  ret.M[9] = M[1]*A.M[8] + M[5]*A.M[9] + M[9]*A.M[10] + M[13]*A.M[11];
  ret.M[10] = M[2]*A.M[8] + M[6]*A.M[9] + M[10]*A.M[10] + M[14]*A.M[11];
  ret.M[11] = M[3]*A.M[8] + M[7]*A.M[9] + M[11]*A.M[10] + M[15]*A.M[11];

  ret.M[12] = M[0]*A.M[12] + M[4]*A.M[13] + M[8]*A.M[14] + M[12]*A.M[15];
  ret.M[13] = M[1]*A.M[12] + M[5]*A.M[13] + M[9]*A.M[14] + M[13]*A.M[15];
  ret.M[14] = M[2]*A.M[12] + M[6]*A.M[13] + M[10]*A.M[14] + M[14]*A.M[15];
  ret.M[15] = M[3]*A.M[12] + M[7]*A.M[13] + M[11]*A.M[14] + M[15]*A.M[15];

  return ret;

}

Vector4 Matrix4::operator*(const Vector3& v)
{
  return v;
}

Vector4 Matrix4::operator*(const Vector4& v)
{
  return v;
}

// Compound Operators
Matrix4& Matrix4::operator+=(const Matrix4& A)
{
  M[0] += A.M[0];
  M[1] += A.M[1];
  M[2] += A.M[2];
  M[3] += A.M[3];

  M[4] += A.M[4];
  M[5] += A.M[5];
  M[6] += A.M[6];
  M[7] += A.M[7];

  M[8] += A.M[8];
  M[9] += A.M[9];
  M[10] += A.M[10];
  M[11] += A.M[11];

  M[12] += A.M[12];
  M[13] += A.M[13];
  M[14] += A.M[14];
  M[15] += A.M[15];

  return *this;
}

Matrix4& Matrix4::operator-=(const Matrix4& A)
{
  M[0] -= A.M[0];
  M[1] -= A.M[1];
  M[2] -= A.M[2];
  M[3] -= A.M[3];

  M[4] -= A.M[4];
  M[5] -= A.M[5];
  M[6] -= A.M[6];
  M[7] -= A.M[7];

  M[8] -= A.M[8];
  M[9] -= A.M[9];
  M[10] -= A.M[10];
  M[11] -= A.M[11];

  M[12] -= A.M[12];
  M[13] -= A.M[13];
  M[14] -= A.M[14];
  M[15] -= A.M[15];

  return *this;
}

Matrix4& Matrix4::operator*=(const float d)
{
  M[0] *= d;
  M[1] *= d;
  M[2] *= d;
  M[3] *= d;

  M[4] *= d;
  M[5] *= d;
  M[6] *= d;
  M[7] *= d;

  M[8] *= d;
  M[9] *= d;
  M[10] *= d;
  M[11] *= d;

  M[12] *= d;
  M[13] *= d;
  M[14] *= d;
  M[15] *= d;

  return *this;
}

Matrix4& Matrix4::operator*=(const Matrix4& A)
{
  Matrix4 T(*this);

  M[0] = T.M[0]*A.M[0] + T.M[4]*A.M[1] + T.M[8]*A.M[2] + T.M[12]*A.M[3];
  M[1] = T.M[1]*A.M[0] + T.M[5]*A.M[1] + T.M[9]*A.M[2] + T.M[13]*A.M[3];
  M[2] = T.M[2]*A.M[0] + T.M[6]*A.M[1] + T.M[10]*A.M[2] + T.M[14]*A.M[3];
  M[3] = T.M[3]*A.M[0] + T.M[7]*A.M[1] + T.M[11]*A.M[2] + T.M[15]*A.M[3];

  M[4] = T.M[0]*A.M[4] + T.M[4]*A.M[5] + T.M[8]*A.M[6] + T.M[12]*A.M[7];
  M[5] = T.M[1]*A.M[4] + T.M[5]*A.M[5] + T.M[9]*A.M[6] + T.M[13]*A.M[7];
  M[6] = T.M[2]*A.M[4] + T.M[6]*A.M[5] + T.M[10]*A.M[6] + T.M[14]*A.M[7];
  M[7] = T.M[3]*A.M[4] + T.M[7]*A.M[5] + T.M[11]*A.M[6] + T.M[15]*A.M[7];

  M[8] = T.M[0]*A.M[8] + T.M[4]*A.M[9] + T.M[8]*A.M[10] + T.M[12]*A.M[11];
  M[9] = T.M[1]*A.M[8] + T.M[5]*A.M[9] + T.M[9]*A.M[10] + T.M[13]*A.M[11];
  M[10] = T.M[2]*A.M[8] + T.M[6]*A.M[9] + T.M[10]*A.M[10] + T.M[14]*A.M[11];
  M[11] = T.M[3]*A.M[8] + T.M[7]*A.M[9] + T.M[11]*A.M[10] + T.M[15]*A.M[11];

  M[12] = T.M[0]*A.M[12] + T.M[4]*A.M[13] + T.M[8]*A.M[14] + T.M[12]*A.M[15];
  M[13] = T.M[1]*A.M[12] + T.M[5]*A.M[13] + T.M[9]*A.M[14] + T.M[13]*A.M[15];
  M[14] = T.M[2]*A.M[12] + T.M[6]*A.M[13] + T.M[10]*A.M[14] + T.M[14]*A.M[15];
  M[15] = T.M[3]*A.M[12] + T.M[7]*A.M[13] + T.M[11]*A.M[14] + T.M[15]*A.M[15];

  return *this;
}

// Stream Operators
std::ostream& operator<<(std::ostream& os, const Matrix4& A)
{
  os << "[ " << A.M[0] << " " << A.M[4] <<
        " " << A.M[8] << " " << A.M[12] << " ]" << std::endl;
  os << "[ " << A.M[1] << " " << A.M[5] <<
        " " << A.M[9] << " " << A.M[13] << " ]" << std::endl;
  os << "[ " << A.M[2] << " " << A.M[6] <<
        " " << A.M[10] << " " << A.M[14] << " ]" << std::endl;
  os << "[ " << A.M[3] << " " << A.M[7] <<
        " " << A.M[11] << " " << A.M[15] << " ]";
  return os;
}

// Accessor Function
float& Matrix4::operator[](unsigned int i)
{
  return M[i];
}

// Misc Operations
void Matrix4::trans()
{
  float a, b, c, d, e, f;

  a = M[1]; b = M[2]; c = M[3];
  d = M[6]; e = M[7];
  f = M[11];

  M[1] = M[4]; M[2] = M[8]; M[3] = M[12];
  M[6] = M[9]; M[7] = M[13];
  M[11] = M[14];

  M[4] = a; M[8] = b; M[12] = c;
  M[9] = d; M[13] = e;
  M[14] = f;

}

void Matrix4::iden()
{
  M[0] = 1; M[1] = 0; M[2] = 0; M[3] = 0;
  M[4] = 0; M[5] = 1; M[6] = 0; M[7] = 0;
  M[8] = 0; M[9] = 0; M[10] = 1; M[11] = 0;
  M[12] = 0; M[13] = 0; M[14] = 0; M[15] = 1;
}
void Matrix4::zero()
{
  M[0] = 0; M[1] = 0; M[2] = 0; M[3] = 0;
  M[4] = 0; M[5] = 0; M[6] = 0; M[7] = 0;
  M[8] = 0; M[9] = 0; M[10] = 0; M[11] = 0;
  M[12] = 0; M[13] = 0; M[14] = 0; M[15] = 0;

}
float Matrix4::det()
{
  return ( M[0]*(
        M[5]*(M[10]*M[15]-M[14]*M[11]) -
      M[9]*(M[6]*M[15]-M[14]*M[7]) +
      M[13]*(M[6]*M[11] - M[10]*M[7])) -
      M[4]*(
      M[1]*(M[10]*M[15]-M[14]*M[11]) -
      M[9]*(M[2]*M[15] - M[14]*M[3]) +
      M[13]*(M[2]*M[11] - M[10]*M[3])) +
      M[8]*(
      M[1]*(M[6]*M[15]-M[14]*M[7]) -
      M[5]*(M[2]*M[15] -M[14]*M[3]) +
      M[13]*(M[2]*M[7] - M[6]*M[3])) -
      M[12]*(
      M[1]*(M[6]*M[11] - M[10]*M[7]) +
      M[5]*(M[2]*M[11] - M[10]*M[3]) -
      M[9]*(M[2]*M[7] - M[6]*M[3])) );

}
Matrix4 Matrix4::invd()
{
  Matrix4 mat;

  mat[0] = M[5]*(M[10]*M[15] - M[14]*M[11]) -
      M[9]*(M[6]*M[15] - M[14]*M[7]) +
      M[13]*(M[6]*M[11] - M[10]*M[7]);
  mat[4] = M[8]*(M[6]*M[15] - M[14]*M[7]) -
      M[12]*(M[6]*M[11] - M[10]*M[7]) -
      M[4]*(M[10]*M[15] - M[14]*M[11]);
  mat[8] = M[4]*(M[9]*M[15] - M[13]*M[11]) -
      M[8]*(M[5]*M[15] - M[13]*M[7]) +
      M[12]*(M[5]*M[11] - M[9]*M[7]);

  mat[12] = M[8]*(M[5]*M[14] - M[13]*M[6]) -
      M[12]*(M[5]*M[10] - M[9]*M[6]) -
      M[4]*(M[9]*M[14] - M[13]*M[10]);
  mat[1] = M[9]*(M[2]*M[15] - M[14]*M[3]) -
      M[13]*(M[2]*M[11] - M[10]*M[3]) -
      M[1]*(M[10]*M[15] - M[14]*M[11]);
  mat[5] = M[0]*(M[10]*M[15] - M[14]*M[11]) -
      M[8]*(M[2]*M[15] - M[14]*M[3]) +
      M[12]*(M[2]*M[11] - M[10]*M[3]);
  mat[9] = - M[0]*(M[9]*M[15] - M[13]*M[11]) +
      M[8]*(M[1]*M[15] - M[13]*M[3]) -
      M[12]*(M[1]*M[11] - M[9]*M[3]);
  mat[13] = M[0]*(M[9]*M[14] - M[13]*M[10]) -
      M[8]*(M[1]*M[14] - M[13]*M[2]) +
      M[12]*(M[1]*M[10] - M[9]*M[2]);

  mat[2] = M[1]*(M[6]*M[15] - M[14]*M[7]) -
      M[5]*(M[2]*M[15] - M[14]*M[3]) +
      M[13]*(M[2]*M[7] - M[6]*M[3]);
  mat[6] = - M[0]*(M[6]*M[15] - M[14]*M[7]) +
      M[4]*(M[2]*M[15] - M[14]*M[3]) -
      M[12]*(M[2]*M[7] - M[6]*M[3]);
  mat[10] = M[0]*(M[5]*M[15] - M[13]*M[7]) -
      M[4]*(M[1]*M[15] - M[13]*M[3]) +
      M[12]*(M[1]*M[7] - M[5]*M[3]);
  mat[14] = - M[0]*(M[5]*M[14] - M[13]*M[6]) +
      M[4]*(M[1]*M[14] - M[13]*M[2]) -
      M[12]*(M[1]*M[6] - M[5]*M[2]);

  mat[3] = - M[1]*(M[6]*M[11] - M[10]*M[7]) +
      M[5]*(M[2]*M[11] - M[10]*M[3]) -
      M[9]*(M[2]*M[7] - M[6]*M[3]);
  mat[7] = M[0]*(M[6]*M[11] - M[10]*M[7]) -
      M[4]*(M[2]*M[11] - M[10]*M[3]) +
      M[8]*(M[2]*M[7] - M[6]*M[3]);
  mat[11] =  - M[0]*(M[5]*M[11] - M[9]*M[7]) +
      M[4]*(M[1]*M[11] - M[9]*M[3]) -
      M[8]*(M[1]*M[7] - M[5]*M[3]);
  mat[15] = M[0]*(M[5]*M[10] - M[9]*M[6]) -
      M[4]*(M[1]*M[10] - M[9]*M[2]) +
      M[8]*(M[1]*M[6] - M[5]*M[2]);

  return mat;

}

Matrix4 operator*(const float &d, const Matrix4 &A) {
  return A*d;
}
