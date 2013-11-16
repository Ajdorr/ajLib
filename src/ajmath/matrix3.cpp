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

vector3::vector3() {
    x = 0;
    y = 0;
    z = 0;
}

vector3::vector3(const vector3 &v) {
    this->x = v.x;
    this->y = v.y;
    this->z = v.z;
}

vector3::vector3(double nx, double ny, double nz) {
    x = nx;
    y = ny;
    z = nz;
}

vector3& vector3::operator=(const vector3 &v) {
    this->x = v.x;
    this->y = v.y;
    this->z = v.z;

    return *this;
}

vector3 vector3::operator+(const vector3 &v) {
    vector3 temp(x+v.x, y+v.y, z+v.z);

    return temp;
}

vector3 vector3::operator-(const vector3 &v) {
    vector3 temp(x-v.x,y-v.y,z-v.z);
    return temp;
}

vector3 vector3::operator%(const vector3 &v){
    vector3 temp((y*v.z) - (z*v.y), (z*v.x) - (x*v.z), (x*v.y)-(y*v.x));

    return temp;
}

double vector3::operator*(const vector3 &v) {
    return v.x*x + v.y*y + v.z*z;
}

vector3& vector3::operator+=(const vector3 &v) {
    this->x = this->x + v.x;
    this->y = this->y + v.y;
    this->z = this->z + v.z;

    return *this;
}

vector3& vector3::operator-=(const vector3 &v) {
    this->x = this->x - v.x;
    this->y = this->y - v.y;
    this->z = this->z - v.z;

    return *this;

}

vector3& vector3::operator%=(const vector3 &v){
    double _x, _y, _z;

    _x = (this->y)*(v.z) - (this->z)*(v.y);
    _y = (this->z)*(v.x) - (this->x)*(v.z);
    _z = (this->x)*(v.y) - (this->y)*(v.x);

    x = _x;
    y = _y;
    z = _z;

    return *this;
}

vector3& vector3::operator*=(const matrix3 &A) {
    double _x, _y, _z;

    _x = x*A.M[0][0] + y*A.M[0][1] + z*A.M[0][2];
    _y = x*A.M[1][0] + y*A.M[1][1] + z*A.M[1][2];
    _z = x*A.M[2][0] + y*A.M[2][1] + z*A.M[2][2];

    x = _x;
    y = _y;
    z = _z;

    return *this;
}

vector3 vector3::operator*(const double a){
    vector3 t(x*a, y*a, z*a);

    return t;
}

vector3 vector3::operator/(const double a) {
    vector3 temp(x/a, y/a,z/a);

    return temp;
}

vector3& vector3::operator*=(const double a){
    x *= a;
    y *= a;
    z *= a;

    return *this;
}

vector3& vector3::operator/=(const double a){
    *this *= 1/a;

    return *this;
}

std::ostream& operator<<(std::ostream& os, const vector3 &v) {
    os << "<" << v.x << ", " << v.y << ", " << v.z << ">";
    return os;
}

bool vector3::operator!=(const vector3 &v) {
        return ( (v.x != this->x) || (v.y != this->y) || (v.z != this->z));
}

bool vector3::operator==(const vector3 &v) {
        return( (v.x == this->x) && (v.y == this->y) && (v.z == this->z));
}


vector3 vector3::Unit() {
    vector3 temp;
    double a = (this->Mag());
    if (a == 0)
        return temp;
    a = 1/a;

    temp.x = x*a;
    temp.y = y*a;
    temp.z = z*a;

    return temp;
}

double vector3::Mag(){
        return sqrt(pow(x,2) + pow(y,2) + pow(z,2));
}

void vector3::Zero() {
        this->x = 0;
        this->y = 0;
        this->z = 0;
}

vector3 operator*(const double &a, const vector3 &v) {
    vector3 t(v);
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
matrix3::matrix3() {
}

matrix3::matrix3(const double a) {
    for (unsigned int i= 0; i < 3; i++) {
        for (unsigned int j= 0; j < 3; j++) {
            if (i == j)
                M[i][j] = a;
            else
                M[i][j] = 0;
        }
    }
}

matrix3::matrix3(const matrix3 &A) {
    for (unsigned int i= 0; i < 3; i++) {
        for (unsigned int j= 0; j < 3; j++) {
            M[i][j] = A.M[i][j];
        }
    }
}

matrix3::matrix3(double d[][3]){
    for (unsigned int i= 0; i < 3; i++) {
        for (unsigned int j= 0; j < 3; j++) {
            M[i][j] = d[i][j];
        }
    }
}

matrix3::matrix3(double **d){
    for (unsigned int i= 0; i < 3; i++) {
        for (unsigned int j= 0; j < 3; j++) {
            M[i][j] = d[i][j];
        }
    }
}

void matrix3::init(double d[][3]) {
    for (unsigned int i= 0; i < 3; i++) {
        for (unsigned int j= 0; j < 3; j++) {
            M[i][j] = d[i][j];
        }
    }
}

void matrix3::init(double **d) {
    for (unsigned int i= 0; i < 3; i++) {
        for (unsigned int j= 0; j < 3; j++) {
            M[i][j] = d[i][j];
        }
    }
}

matrix3& matrix3::operator=(const double d) {
    for (unsigned int i= 0; i < 3; i++) {
        for (unsigned int j= 0; j < 3; j++) {
            M[i][j] = d;
        }
    }
    return *this;
}

matrix3& matrix3::operator=(const matrix3 &A){
    if (&A == this)
        return *this;
    for (unsigned int i= 0; i < 3; i++) {
        for (unsigned int j= 0; j < 3; j++) {
            M[i][j] = A.M[i][j];
        }
    }
    return *this;
}

matrix3 matrix3::operator+(const matrix3 &A) {
    matrix3 ret;
    for (unsigned int i= 0; i < 3; i++) {
        for (unsigned int j= 0; j < 3; j++) {
            ret.M[i][j] = M[i][j] + A.M[i][j];
        }
    }
    return ret;
}

matrix3 matrix3::operator-(const matrix3 &A) {
    matrix3 ret;
    for (unsigned int i= 0; i < 3; i++) {
        for (unsigned int j= 0; j < 3; j++) {
            ret.M[i][j] = M[i][j] - A.M[i][j];
        }
    }
    return ret;
}

matrix3 matrix3::operator*(const double d) {
    matrix3 ret;
    for (unsigned int i= 0; i < 3; i++)
        for (unsigned int j= 0; j < 3; j++)
            ret.M[i][j] = M[i][j] * d;
    return ret;
}

matrix3 matrix3::operator/(const double d) {
    double a = 1/d;
    matrix3 ret;
    for (unsigned int i= 0; i < 3; i++)
        for (unsigned int j= 0; j < 3; j++)
            ret.M[i][j] = M[i][j] * a;
    return ret;
}


matrix3 matrix3::operator*(const matrix3 &A) {
    unsigned int i, j;
    matrix3 ret;
    for (i= 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            ret.M[i][j] = (M[i][0])*(A.M[0][j]);
            ret.M[i][j] += (M[i][1])*(A.M[1][j]);
            ret.M[i][j] += (M[i][2])*(A.M[2][j]);
        }
    }

    return ret;
}

vector3 matrix3::operator*(const vector3 &v) {
    vector3 ret;

    ret.x = v.x*M[0][0] + v.y*M[0][1] + v.z*M[0][2];
    ret.y = v.x*M[1][0] + v.y*M[1][1] + v.z*M[1][2];
    ret.z = v.x*M[2][0] + v.y*M[2][1] + v.z*M[2][2];

    return ret;
}

// Compound Operators
matrix3& matrix3::operator+=(const matrix3 &A) {
    for (unsigned int i= 0; i < 9; i++)
        M[i/3][i%3] += A.M[i/3][i%3];

    return *this;
}

matrix3& matrix3::operator-=(const matrix3 &A) {
    for (unsigned int i= 0; i < 9; i++)
        M[i/3][i%3] -= A.M[i/3][i%3];

    return *this;
}

matrix3& matrix3::operator*=(const double d) {
    for (unsigned int i= 0; i < 9; i++)
        M[i/3][i%3] *= d;

    return *this;
}

matrix3& matrix3::operator*=(const matrix3 &A) {
    unsigned int i, j;
    matrix3 cpy(*this);
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
std::ostream& operator<<(std::ostream &os, const matrix3 &A) {
    os << "[ " << A.M[0][0] << " " << A.M[0][1] << " " << A.M[0][2]  << " ]" << endl;
    os << "[ " << A.M[1][0] << " " << A.M[1][1] << " " << A.M[1][2]  << " ]" << endl;
    os << "[ " << A.M[2][0] << " " << A.M[2][1] << " " << A.M[2][2]  << " ]";

    return os;
}

// Accessor Function
double* matrix3::operator[](unsigned int x) {
    return M[x];
}

// Misc Operations
void matrix3::trans() {
    double t;

    SWAPT(M[0][1], M[1][0], t);
    SWAPT(M[0][2], M[2][0], t);
    SWAPT(M[1][2], M[2][1], t);
}

void matrix3::iden(){
    for (unsigned int i= 0; i < 9; i++) {
        if (i%3 == i/3)
            M[i/3][i%3] = 1;
        else
            M[i/3][i%3] = 0;
    }
}

void matrix3::zero() {
    for (unsigned int i = 0; i < 9; i++)
        M[i/3][i%3] = 0;
}

double matrix3::det(){
    double ret = M[0][0]*((M[1][1] * M[2][2]) - (M[1][2]*M[2][1]) );
    ret -= M[1][0]*( (M[0][1]*M[2][2]) - (M[2][1]*M[0][2]) );
    ret += M[2][0]*( (M[0][1]*M[1][2]) - (M[1][1]*M[0][2]) );
    return ret;
}

matrix3 matrix3::inv() {
    matrix3 inv;

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

matrix3 operator*(const double &d, const matrix3 &A) {
    matrix3 ret = A;

    return ret*d;
}
