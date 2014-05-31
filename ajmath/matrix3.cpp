#include <math.h>
#include "matrix3.h"

/*
 *
 *
 * 3 Dimensional Vector Class
 *
 *
 */

// static Member Variables

Vector3 Vector3::Zero = Vector3(0,0,0);
Vector3 Vector3::One = Vector3(1,1,1);

Vector3::Vector3(const Vector3 &vec) {
  v[0] = vec.v[0];
  v[1] = vec.v[1];
  v[2] = vec.v[2];
}

Vector3::Vector3(float nx, float ny, float nz) {
  v[0] = nx;
  v[1] = ny;
  v[2] = nz;
}

Vector3& Vector3::operator=(const Vector3 &vec) {
  v[0] = vec.v[0];
  v[1] = vec.v[1];
  v[2] = vec.v[2];

  return *this;
}

Vector3 Vector3::operator+(const Vector3 &vec) {
  Vector3 ret(vec.v[0] + v[0], vec.v[1] + v[1], vec.v[2] + v[2]);

  return ret;
}

Vector3 Vector3::operator-(const Vector3 &vec) {
  Vector3 ret(v[0] - vec.v[0], v[1] - vec.v[1], v[2] - vec.v[2]);
  return ret;
}

Vector3 Vector3::operator^(const Vector3 &vec){
  Vector3 ret;

  ret.v[0] = v[1]*vec.v[2] - v[2]*vec.v[1];
  ret.v[1] = v[2]*vec.v[0] - v[0]*vec.v[2];
  ret.v[2] = v[0]*vec.v[1] - v[1]*vec.v[0];

  return ret;
}

float Vector3::operator*(const Vector3 &vec) {
  return v[0]*vec.v[0] + v[1]*vec.v[1] + v[2]*vec.v[2];
}

Vector3& Vector3::operator+=(const Vector3 &vec) {
  v[0] += vec.v[0];
  v[1] += vec.v[1];
  v[2] += vec.v[2];

  return *this;
}

Vector3& Vector3::operator-=(const Vector3 &vec) {
  v[0] -= vec.v[0];
  v[1] -= vec.v[1];
  v[2] -= vec.v[2];

  return *this;

}

Vector3& Vector3::operator^=(const Vector3 &vec){
  float _x, _y, _z;

  _x = v[1]*vec.v[2] - v[2]*vec.v[1];
  _y = v[2]*vec.v[0] - v[0]*vec.v[2];
  _z = v[0]*vec.v[1] - v[1]*vec.v[0];

  v[0] = _x;
  v[1] = _y;
  v[2] = _z;

  return *this;
}

Vector3 Vector3::operator*(const float a){
  Vector3 t(v[0]*a, v[1]*a, v[2]*a);

  return t;
}

Vector3 Vector3::operator/(const float a) {
  Vector3 temp(v[0]/a, v[1]/a, v[2]/a);

  return temp;
}

Vector3& Vector3::operator*=(const float a){
  v[0] *= a;
  v[1] *= a;
  v[2] *= a;

  return *this;
}

Vector3& Vector3::operator/=(const float a){
  float d = 1/a;
  v[0] *= d;
  v[1] *= d;
  v[2] *= d;

  return *this;
}

std::ostream& operator<<(std::ostream& os, const Vector3 &vec) {
  os << "<" << vec.v[0] << ", " << vec.v[1] << ", " << vec.v[2] << ">";
  return os;
}

bool Vector3::operator!=(const Vector3 &vec) {
  return (vec.v[0] != v[0]) ||
      (vec.v[1] != v[1]) ||
      (vec.v[2] != v[2]);
}

bool Vector3::operator==(const Vector3 &vec) {
  return (vec.v[0] == v[0]) &&
      (vec.v[1] == v[1]) &&
      (vec.v[2] == v[2]);
}

float& Vector3::operator[](int i) { return v[i]; }

float Vector3::x() const { return v[0]; }
float Vector3::y() const { return v[1]; }
float Vector3::z() const { return v[2]; }

Vector3 Vector3::unit() {
  Vector3 temp;
  float a = (this->mag());
  if (a == 0) return temp;
  a = 1/a;

  temp.v[0] = v[0]*a;
  temp.v[1] = v[1]*a;
  temp.v[2] = v[2]*a;

  return temp;
}

void Vector3::setUnit()
{
  float a = mag();
  if (a == 0) return;
  a = 1/a;

  v[0] *= a;
  v[1] *= a;
  v[2] *= a;
}

float Vector3::mag(){
  // fix this
  return sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
}

float Vector3::mag2(){
  // fix this
  return v[0]*v[0] + v[1]*v[1] + v[2]*v[2];
}

Vector3 operator*(const float &a, const Vector3 &vec) {
  Vector3 ret(a*vec.x(), a*vec.y(), a*vec.z());
  return ret;
}


/*
 *
 *
 * 3 Dimensional Matrix Class
 *
 *
 */

// Constructors
Matrix3::Matrix3(const float a)
{
  M[0] = a; M[1] = 0; M[2] = 0;
  M[3] = 0; M[4] = a; M[5] = 0;
  M[6] = 0; M[7] = 0; M[8] = a;
}

Matrix3::Matrix3(const Matrix3 &A)
{
  M[0] = A.M[0]; M[1] = A.M[1]; M[2] = A.M[2];
  M[3] = A.M[3]; M[4] = A.M[4]; M[5] = A.M[5];
  M[6] = A.M[6]; M[7] = A.M[7]; M[8] = A.M[8];
}

Matrix3::Matrix3(const float *d)
{
  M[0] = d[0]; M[1] = d[1]; M[2] = d[2];
  M[3] = d[3]; M[4] = d[4]; M[5] = d[5];
  M[6] = d[6]; M[7] = d[7]; M[8] = d[8];
}

Matrix3::Matrix3(const float **d)
{
  M[0] = d[0][0]; M[1] = d[0][1]; M[2] = d[0][2];
  M[3] = d[1][0]; M[4] = d[1][1]; M[5] = d[1][2];
  M[6] = d[2][0]; M[7] = d[2][1]; M[8] = d[2][2];
}

Matrix3::Matrix3(const float d[][3])
{
  M[0] = d[0][0]; M[1] = d[0][1]; M[2] = d[0][2];
  M[3] = d[1][0]; M[4] = d[1][1]; M[5] = d[1][2];
  M[6] = d[2][0]; M[7] = d[2][1]; M[8] = d[2][2];
}

// Assignment Operators
Matrix3& Matrix3::operator=(const float *d)
{
  M[0] = d[0]; M[1] = d[1]; M[2] = d[2];
  M[3] = d[3]; M[4] = d[4]; M[5] = d[5];
  M[6] = d[6]; M[7] = d[7]; M[8] = d[8];

  return *this;
}

Matrix3& Matrix3::operator=(const float **d)
{
  M[0] = d[0][0]; M[1] = d[0][1]; M[2] = d[0][2];
  M[3] = d[1][0]; M[4] = d[1][1]; M[5] = d[1][2];
  M[6] = d[2][0]; M[7] = d[2][1]; M[8] = d[2][2];

  return *this;
}

Matrix3& Matrix3::operator=(const float d[][3])
{
  M[0] = d[0][0]; M[1] = d[0][1]; M[2] = d[0][2];
  M[3] = d[1][0]; M[4] = d[1][1]; M[5] = d[1][2];
  M[6] = d[2][0]; M[7] = d[2][1]; M[8] = d[2][2];

  return *this;
}

Matrix3& Matrix3::operator=(const float d)
{
  M[0] = d; M[1] = 0; M[2] = 0;
  M[3] = 0; M[4] = d; M[5] = 0;
  M[6] = 0; M[7] = 0; M[8] = d;

  return *this;
}

Matrix3& Matrix3::operator=(const Matrix3 &A){
  M[0] = A.M[0]; M[1] = A.M[1]; M[2] = A.M[2];
  M[3] = A.M[3]; M[4] = A.M[4]; M[5] = A.M[5];
  M[6] = A.M[6]; M[7] = A.M[7]; M[8] = A.M[8];

  return *this;
}

// Arithmetic Operators
Matrix3 Matrix3::operator+(const Matrix3 &A) {
  Matrix3 ret;

  ret.M[0] = M[0] + A.M[0];
  ret.M[1] = M[1] + A.M[1];
  ret.M[2] = M[2] + A.M[2];

  ret.M[3] = M[3] + A.M[3];
  ret.M[4] = M[4] + A.M[4];
  ret.M[5] = M[5] + A.M[5];

  ret.M[6] = M[6] + A.M[6];
  ret.M[7] = M[7] + A.M[7];
  ret.M[8] = M[8] + A.M[8];

  return ret;
}

Matrix3 Matrix3::operator-(const Matrix3 &A) {
  Matrix3 ret;

  ret.M[0] = M[0] - A.M[0];
  ret.M[1] = M[1] - A.M[1];
  ret.M[2] = M[2] - A.M[2];

  ret.M[3] = M[3] - A.M[3];
  ret.M[4] = M[4] - A.M[4];
  ret.M[5] = M[5] - A.M[5];

  ret.M[6] = M[6] - A.M[6];
  ret.M[7] = M[7] - A.M[7];
  ret.M[8] = M[8] - A.M[8];

  return ret;
}

Matrix3 Matrix3::operator*(const float d) const
{
  Matrix3 ret;

  ret.M[0] = M[0] * d;
  ret.M[1] = M[1] * d;
  ret.M[2] = M[2] * d;

  ret.M[3] = M[3] * d;
  ret.M[4] = M[4] * d;
  ret.M[5] = M[5] * d;

  ret.M[6] = M[6] * d;
  ret.M[7] = M[7] * d;
  ret.M[8] = M[8] * d;

  return ret;
}

Matrix3 Matrix3::operator/(const float a) {
  Matrix3 ret;
  float d = 1/a;

  ret.M[0] = M[0] * d;
  ret.M[1] = M[1] * d;
  ret.M[2] = M[2] * d;

  ret.M[3] = M[3] * d;
  ret.M[4] = M[4] * d;
  ret.M[5] = M[5] * d;

  ret.M[6] = M[6] * d;
  ret.M[7] = M[7] * d;
  ret.M[8] = M[8] * d;

  return ret;
}


Matrix3 Matrix3::operator*(const Matrix3 &A) {
  Matrix3 ret;

  ret.M[0] = M[0] * A.M[0] + M[3] * A.M[1] + M[6] * A.M[2];
  ret.M[1] = M[1] * A.M[0] + M[4] * A.M[1] + M[7] * A.M[2];
  ret.M[2] = M[2] * A.M[0] + M[5] * A.M[1] + M[8] * A.M[2];

  ret.M[3] = M[0] * A.M[3] + M[3] * A.M[4] + M[6] * A.M[5];
  ret.M[4] = M[1] * A.M[3] + M[4] * A.M[4] + M[7] * A.M[5];
  ret.M[5] = M[2] * A.M[3] + M[5] * A.M[4] + M[8] * A.M[5];

  ret.M[6] = M[0] * A.M[6] + M[3] * A.M[7] + M[6] * A.M[8];
  ret.M[7] = M[1] * A.M[6] + M[4] * A.M[7] + M[7] * A.M[8];
  ret.M[8] = M[2] * A.M[6] + M[5] * A.M[7] + M[8] * A.M[8];

  return ret;
}

Vector3 Matrix3::operator*(const Vector3 &vec) {
  Vector3 ret(vec.x()*M[0] + vec.y()*M[3] + vec.z()*M[6],
      vec.x()*M[1] + vec.y()*M[4] + vec.z()*M[7],
      vec.x()*M[2] + vec.y()*M[5] + vec.z()*M[8] );

  return ret;
}

// Compound Operators
Matrix3& Matrix3::operator+=(const Matrix3 &A) {
  M[0] += A.M[0]; M[3] += A.M[3]; M[6] += A.M[6];
  M[1] += A.M[1]; M[4] += A.M[4]; M[7] += A.M[7];
  M[2] += A.M[2]; M[5] += A.M[5]; M[8] += A.M[8];

  return *this;
}

Matrix3& Matrix3::operator-=(const Matrix3 &A) {
  M[0] -= A.M[0]; M[3] -= A.M[3]; M[6] -= A.M[6];
  M[1] -= A.M[1]; M[4] -= A.M[4]; M[7] -= A.M[7];
  M[2] -= A.M[2]; M[5] -= A.M[5]; M[8] -= A.M[8];

  return *this;
}

Matrix3& Matrix3::operator*=(const float d) {
  M[0] *= d; M[3] *= d; M[6] *= d;
  M[1] *= d; M[4] *= d; M[7] *= d;
  M[2] *= d; M[5] *= d; M[8] *= d;

  return *this;
}

Matrix3& Matrix3::operator*=(const Matrix3 &A)
{
  Matrix3 T(*this);

  M[0] = T.M[0]*A.M[0] + T.M[3]*A.M[1] + T.M[6]*A.M[2];
  M[1] = T.M[1]*A.M[0] + T.M[4]*A.M[1] + T.M[7]*A.M[2];
  M[2] = T.M[2]*A.M[0] + T.M[5]*A.M[1] + T.M[8]*A.M[2];

  M[3] = T.M[0]*A.M[3] + T.M[3]*A.M[4] + T.M[6]*A.M[5];
  M[4] = T.M[1]*A.M[3] + T.M[4]*A.M[4] + T.M[7]*A.M[5];
  M[5] = T.M[2]*A.M[3] + T.M[5]*A.M[4] + T.M[8]*A.M[5];

  M[6] = T.M[0]*A.M[6] + T.M[3]*A.M[7] + T.M[6]*A.M[8];
  M[7] = T.M[1]*A.M[6] + T.M[4]*A.M[7] + T.M[7]*A.M[8];
  M[8] = T.M[2]*A.M[6] + T.M[5]*A.M[7] + T.M[8]*A.M[8];

  return *this;
}

// Stream Operators
std::ostream& operator<<(std::ostream &os, const Matrix3 &A)
{

  os << "[ " << A.M[0] << " " << A.M[3] << " " << A.M[6] << std::endl;
  os << "[ " << A.M[1] << " " << A.M[4] << " " << A.M[7] << std::endl;
  os << "[ " << A.M[2] << " " << A.M[5] << " " << A.M[8];

  return os;
}

// Accessor Function
float& Matrix3::operator[](unsigned int x) {
  return M[x];
}

// Misc Operations
void Matrix3::trans() {
  float a, b, c;

  a = M[1]; b = M[2]; c = M[5];
  M[1] = M[3]; M[2] = M[6]; M[5] = M[7];
  M[3] = a; M[6] = b; M[7] = c;
}

void Matrix3::iden(){
  M[0] = 1; M[1] = 0; M[2] = 0;
  M[3] = 0; M[4] = 1; M[5] = 0;
  M[6] = 0; M[7] = 0; M[8] = 1;
}

void Matrix3::zero() {
  M[0] = 0; M[1] = 0; M[2] = 0;
  M[3] = 0; M[4] = 0; M[5] = 0;
  M[6] = 0; M[7] = 0; M[8] = 0;
}

float Matrix3::det(){
  return ( M[0]*(M[4]*M[8] - M[5]*M[7]) -
      M[1]*(M[1]*M[8] - M[2]*M[7]) +
      M[2]*(M[1]*M[5] - M[2]*M[4]) );
}

Matrix3 Matrix3::invd() {
  Matrix3 inv;

  inv.M[0] = M[4]*M[8] - M[5]*M[7];
  inv.M[3] = M[5]*M[6] - M[3]*M[8];
  inv.M[6] = M[3]*M[7] - M[4]*M[6];

  inv.M[1] = M[2]*M[7] - M[1]*M[8];
  inv.M[4] = M[0]*M[8] - M[2]*M[6];
  inv.M[7] = M[1]*M[6] - M[0]*M[7];

  inv.M[2] = M[1]*M[5] - M[2]*M[4];
  inv.M[5] = M[2]*M[3] - M[0]*M[5];
  inv.M[8] = M[0]*M[4] - M[1]*M[3];

  return inv;
}

Matrix3 operator*(const float &d, const Matrix3 &A) {
  return A*d;
}
