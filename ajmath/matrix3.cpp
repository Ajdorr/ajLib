#include <math.h>
#include "matrix3.h"
#include "ajmath.h"

/*
 *
 *
 * 3 Dimensional Vector Class
 *
 *
 */

Vector3::Vector3() {
    x = 0;
    y = 0;
    z = 0;
}

Vector3::Vector3(const Vector3 &v) {
    this->x = v.x;
    this->y = v.y;
    this->z = v.z;
}

Vector3::Vector3(double nx, double ny, double nz) {
    x = nx;
    y = ny;
    z = nz;
}

Vector3& Vector3::operator=(const Vector3 &v) {
    this->x = v.x;
    this->y = v.y;
    this->z = v.z;

    return *this;
}

Vector3 Vector3::operator+(const Vector3 &v) {
    Vector3 temp(x+v.x, y+v.y, z+v.z);

    return temp;
}

Vector3 Vector3::operator-(const Vector3 &v) {
    Vector3 temp(x-v.x,y-v.y,z-v.z);
    return temp;
}

Vector3 Vector3::operator%(const Vector3 &v){
    Vector3 temp((y*v.z) - (z*v.y), (z*v.x) - (x*v.z), (x*v.y)-(y*v.x));

    return temp;
}

double Vector3::operator*(const Vector3 &v) {
    return v.x*x + v.y*y + v.z*z;
}

Vector3& Vector3::operator+=(const Vector3 &v) {
    this->x = this->x + v.x;
    this->y = this->y + v.y;
    this->z = this->z + v.z;

    return *this;
}

Vector3& Vector3::operator-=(const Vector3 &v) {
    this->x = this->x - v.x;
    this->y = this->y - v.y;
    this->z = this->z - v.z;

    return *this;

}

Vector3& Vector3::operator%=(const Vector3 &v){
    double _x, _y, _z;

    _x = (this->y)*(v.z) - (this->z)*(v.y);
    _y = (this->z)*(v.x) - (this->x)*(v.z);
    _z = (this->x)*(v.y) - (this->y)*(v.x);

    x = _x;
    y = _y;
    z = _z;

    return *this;
}

Vector3& Vector3::operator*=(const Matrix3 &A) {
    double _x, _y, _z;

    _x = x*A.M[0][0] + y*A.M[0][1] + z*A.M[0][2];
    _y = x*A.M[1][0] + y*A.M[1][1] + z*A.M[1][2];
    _z = x*A.M[2][0] + y*A.M[2][1] + z*A.M[2][2];

    x = _x;
    y = _y;
    z = _z;

    return *this;
}

Vector3 Vector3::operator*(const double a){
    Vector3 t(x*a, y*a, z*a);

    return t;
}

Vector3 Vector3::operator/(const double a) {
    Vector3 temp(x/a, y/a,z/a);

    return temp;
}

Vector3& Vector3::operator*=(const double a){
    x *= a;
    y *= a;
    z *= a;

    return *this;
}

Vector3& Vector3::operator/=(const double a){
    *this *= 1/a;

    return *this;
}

std::ostream& operator<<(std::ostream& os, const Vector3 &v) {
    os << "<" << v.x << ", " << v.y << ", " << v.z << ">";
    return os;
}

bool Vector3::operator!=(const Vector3 &v) {
        return ( (v.x != this->x) || (v.y != this->y) || (v.z != this->z));
}

bool Vector3::operator==(const Vector3 &v) {
        return( (v.x == this->x) && (v.y == this->y) && (v.z == this->z));
}


Vector3 Vector3::Unit() {
    Vector3 temp;
    double a = (this->Mag());
    if (a == 0)
        return temp;
    a = 1/a;

    temp.x = x*a;
    temp.y = y*a;
    temp.z = z*a;

    return temp;
}

double Vector3::Mag(){
        return sqrt(pow(x,2) + pow(y,2) + pow(z,2));
}

void Vector3::Zero() {
        this->x = 0;
        this->y = 0;
        this->z = 0;
}

Vector3 operator*(const double &a, const Vector3 &v) {
    Vector3 t(v);
    t*=a;
    return t;
}


/*
 *
 *
 * 3 Dimensional Matrix Class
 *
 *
 */

// Constructors
Matrix3::Matrix3() {
}

Matrix3::Matrix3(const double a) {
    for (unsigned int i= 0; i < 3; i++) {
        for (unsigned int j= 0; j < 3; j++) {
            if (i == j)
                M[i][j] = a;
            else
                M[i][j] = 0;
        }
    }
}

Matrix3::Matrix3(const Matrix3 &A) {
    for (unsigned int i= 0; i < 3; i++) {
        for (unsigned int j= 0; j < 3; j++) {
            M[i][j] = A.M[i][j];
        }
    }
}

Matrix3::Matrix3(double d[][3]){
    for (unsigned int i= 0; i < 3; i++) {
        for (unsigned int j= 0; j < 3; j++) {
            M[i][j] = d[i][j];
        }
    }
}

Matrix3::Matrix3(double **d){
    for (unsigned int i= 0; i < 3; i++) {
        for (unsigned int j= 0; j < 3; j++) {
            M[i][j] = d[i][j];
        }
    }
}

void Matrix3::init(double d[][3]) {
    for (unsigned int i= 0; i < 3; i++) {
        for (unsigned int j= 0; j < 3; j++) {
            M[i][j] = d[i][j];
        }
    }
}

void Matrix3::init(double **d) {
    for (unsigned int i= 0; i < 3; i++) {
        for (unsigned int j= 0; j < 3; j++) {
            M[i][j] = d[i][j];
        }
    }
}

Matrix3& Matrix3::operator=(const double d) {
    for (unsigned int i= 0; i < 3; i++) {
        for (unsigned int j= 0; j < 3; j++) {
            M[i][j] = d;
        }
    }
    return *this;
}

Matrix3& Matrix3::operator=(const Matrix3 &A){
    if (&A == this)
        return *this;
    for (unsigned int i= 0; i < 3; i++) {
        for (unsigned int j= 0; j < 3; j++) {
            M[i][j] = A.M[i][j];
        }
    }
    return *this;
}

Matrix3 Matrix3::operator+(const Matrix3 &A) {
    Matrix3 ret;
    for (unsigned int i= 0; i < 3; i++) {
        for (unsigned int j= 0; j < 3; j++) {
            ret.M[i][j] = M[i][j] + A.M[i][j];
        }
    }
    return ret;
}

Matrix3 Matrix3::operator-(const Matrix3 &A) {
    Matrix3 ret;
    for (unsigned int i= 0; i < 3; i++) {
        for (unsigned int j= 0; j < 3; j++) {
            ret.M[i][j] = M[i][j] - A.M[i][j];
        }
    }
    return ret;
}

Matrix3 Matrix3::operator*(const double d) {
    Matrix3 ret;
    for (unsigned int i= 0; i < 3; i++)
        for (unsigned int j= 0; j < 3; j++)
            ret.M[i][j] = M[i][j] * d;
    return ret;
}

Matrix3 Matrix3::operator/(const double d) {
    double a = 1/d;
    Matrix3 ret;
    for (unsigned int i= 0; i < 3; i++)
        for (unsigned int j= 0; j < 3; j++)
            ret.M[i][j] = M[i][j] * a;
    return ret;
}


Matrix3 Matrix3::operator*(const Matrix3 &A) {
    unsigned int i, j;
    Matrix3 ret;
    for (i= 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            ret.M[i][j] = (M[i][0])*(A.M[0][j]);
            ret.M[i][j] += (M[i][1])*(A.M[1][j]);
            ret.M[i][j] += (M[i][2])*(A.M[2][j]);
        }
    }

    return ret;
}

Vector3 Matrix3::operator*(const Vector3 &v) {
    Vector3 ret;

    ret.x = v.x*M[0][0] + v.y*M[0][1] + v.z*M[0][2];
    ret.y = v.x*M[1][0] + v.y*M[1][1] + v.z*M[1][2];
    ret.z = v.x*M[2][0] + v.y*M[2][1] + v.z*M[2][2];

    return ret;
}

// Compound Operators
Matrix3& Matrix3::operator+=(const Matrix3 &A) {
    for (unsigned int i= 0; i < 9; i++)
        M[i/3][i%3] += A.M[i/3][i%3];

    return *this;
}

Matrix3& Matrix3::operator-=(const Matrix3 &A) {
    for (unsigned int i= 0; i < 9; i++)
        M[i/3][i%3] -= A.M[i/3][i%3];

    return *this;
}

Matrix3& Matrix3::operator*=(const double d) {
    for (unsigned int i= 0; i < 9; i++)
        M[i/3][i%3] *= d;

    return *this;
}

Matrix3& Matrix3::operator*=(const Matrix3 &A) {
    unsigned int i, j;
    Matrix3 cpy(*this);
    for (i= 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            M[i][j] = (cpy.M[i][0])*(A.M[0][j]);
            M[i][j] += (cpy.M[i][1])*(A.M[1][j]);
            M[i][j] += (cpy.M[i][2])*(A.M[2][j]);
        }
    }
    return *this;
}

// Stream Operators
std::ostream& operator<<(std::ostream &os, const Matrix3 &A) {
    os << "[ " << A.M[0][0] << " " << A.M[0][1] << " " << A.M[0][2]  << " ]" << endl;
    os << "[ " << A.M[1][0] << " " << A.M[1][1] << " " << A.M[1][2]  << " ]" << endl;
    os << "[ " << A.M[2][0] << " " << A.M[2][1] << " " << A.M[2][2]  << " ]";

    return os;
}

// Accessor Function
double* Matrix3::operator[](unsigned int x) {
    return M[x];
}

// Misc Operations
void Matrix3::trans() {
    double t;

    SWAPT(M[0][1], M[1][0], t);
    SWAPT(M[0][2], M[2][0], t);
    SWAPT(M[1][2], M[2][1], t);
}

void Matrix3::iden(){
    for (unsigned int i= 0; i < 9; i++) {
        if (i%3 == i/3)
            M[i/3][i%3] = 1;
        else
            M[i/3][i%3] = 0;
    }
}

void Matrix3::zero() {
    for (unsigned int i = 0; i < 9; i++)
        M[i/3][i%3] = 0;
}

double Matrix3::det(){
    double ret = M[0][0]*((M[1][1] * M[2][2]) - (M[1][2]*M[2][1]) );
    ret -= M[1][0]*( (M[0][1]*M[2][2]) - (M[2][1]*M[0][2]) );
    ret += M[2][0]*( (M[0][1]*M[1][2]) - (M[1][1]*M[0][2]) );
    return ret;
}

Matrix3 Matrix3::inv() {
    Matrix3 inv;

    inv.M[0][0] = M[1][1]*M[2][2] - M[1][2]*M[2][1];
    inv.M[0][1] = M[0][2]*M[2][1] - M[0][1]*M[2][2];
    inv.M[0][2] = M[0][1]*M[1][2] - M[0][2]*M[1][1];

    inv.M[1][0] = M[1][2]*M[2][0] - M[1][0]*M[2][2];
    inv.M[1][1] = M[0][0]*M[2][2] - M[0][2]*M[2][0];
    inv.M[1][2] = M[0][2]*M[1][0] - M[0][0]*M[1][2];

    inv.M[2][0] = M[1][0]*M[2][1] - M[1][1]*M[2][0];
    inv.M[2][1] = M[0][1]*M[2][0] - M[0][0]*M[2][1];
    inv.M[2][2] = M[0][0]*M[1][1] - M[0][1]*M[1][0];

    return inv;
}

Matrix3 operator*(const double &d, const Matrix3 &A) {
    Matrix3 ret = A;

    return ret*d;
}
