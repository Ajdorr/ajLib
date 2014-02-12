#include <iostream>
#include <math.h>
#include "ajmath.h"
#include "matrix.h"
#include "sequence.h"

using namespace std;

/*
 *
 *
 * N dimensional Vector Class
 *
 *
 */

VectorN::VectorN(){
    V = NULL;
    n = 0;
}

VectorN::VectorN(const VectorN &v) {
    n = v.n;
    V = new double[n];
    for (unsigned int i = 0; i < v.n; i++)
        V[i] = v.V[i];
}

VectorN::VectorN(double *_v, unsigned int _n){
    n = _n;
    V = new double[n];
    for (unsigned int i = 0; i < _n; i++)
        V[i] = _v[i];
}

VectorN::~VectorN() {
    if (V)
        delete[] V;
    n = 0;
}

VectorN& VectorN::operator=(const VectorN &v) {
    if (&v == this)
        return *this;
    if (V)
        delete[] V;

    n = v.n;
    V = new double[n];
    for (unsigned int i = 0; i < v.n; i++) // deep copy
        V[i] = v.V[i];

    return *this;
}

// Vector Argumented Operations
VectorN VectorN::operator+(const VectorN &v) {
    VectorN ng;
    if (v.n != n)
        return ng;

    ng.n = n;
    ng.V = new double[n];

    for (unsigned int i = 0; i < n; i++)
        ng.V[i] = V[i] + v.V[i];

    return ng;
}

VectorN VectorN::operator-(const VectorN &v){
    VectorN ng;
    if (v.n != n)
        return ng;

    ng.n = n;
    ng.V = new double[n];

    for (unsigned int i = 0; i < n; i++)
        ng.V[i] = V[i] - v.V[i];

    return ng;
}

VectorN& VectorN::operator+=(const VectorN &v) {
    if (v.n != n)
        return *this;

    for (unsigned int i = 0; i < n; i++)
        V[i] += v.V[i];

    return *this;
}


VectorN& VectorN::operator-=(const VectorN &v){
    if (v.n != n)
        return *this;

    for (unsigned int i = 0; i < n; i++)
        V[i] -= v.V[i];

    return *this;
}

VectorN& VectorN::operator*=(const Matrix &A) {
    unsigned int i, j;
    double *t;

    if (A.m != n)
        return *this;
    t = new double[A.n];

    for (i = 0; i < A.n; i++){
        t[i] = 0;
        for (j = 0; j < A.m; j++)
            t[i] += V[j] * A.M[i][j];
    }

    delete[] V;
    V = t;
    n = A.n;

    return *this;
}


double VectorN::operator*(const VectorN &v) {
    double ret = 0;
    if (v.n != n)
        return ret;

    for (unsigned int i = 0; i < n; i++)
        ret += V[i] * v.V[i];

    return ret;
}


// Scalar argumented operations
VectorN VectorN::operator*(const double a) {
    VectorN ng(*this);

    ng *=a;

    return ng;
}

VectorN VectorN::operator/(const double a) {
    VectorN ng(*this);

    ng *= 1/a;

    return ng;
}

// Compound Operations
VectorN& VectorN::operator*=(const double a) {
    for (unsigned int i = 0; i < n; i++)
        V[i] *= a;

    return *this;
}

VectorN& VectorN::operator/=(const double a){
    *this *= 1/a;

    return *this;
}

// Accessibility Operators
double& VectorN::operator[](const int i) {
    return V[i];
}

std::ostream& operator<<(std::ostream &os, const VectorN &v){
    unsigned int i;
    os << "<";
    if (v.n == 0){
        os << ">";
        return os;
    }
    for (i = 0; i < v.n-1; i++)
        os << v.V[i] << ", ";

    os << v.V[i] << ">";

    return os;
}

unsigned int VectorN::dim() const {
    return n;
}

VectorN VectorN::unit() {
    VectorN ng;
    double mg = this->mag();
    if (mg == 0)
        return ng;

    ng = *this;
    ng /= mg;

    return ng;
}

double VectorN::mag() {
    double ret = 0;
    for (unsigned int i = 0; i < n; i++)
        ret += V[i]*V[i];

    return sqrt(ret);
}

void VectorN::zero(){
    for (unsigned int i = 0; i < n; i++)
        V[i] = 0;

}

VectorN operator*(const double &a, const VectorN &v) {
    VectorN ng(v);
    ng *= a;
    return ng;
}

/*
 *
 *
 *
 * N Dimensional Matrix Class
 *
 *
 *
 */

/*
 *
 * Private Functions
 *
 */

void Matrix::delMat() {
    unsigned int i;

    for (i = 0; i < n; i++)
        delete[] M[i];
    delete[] M;
}

// using row zero out index (x,y)
// returns the multiplication factor
double Matrix::zeroOnIndex(unsigned int row, unsigned int x, unsigned int y) {
    double t = -M[x][y]/M[row][y];
    unsigned int i;

    for (i = (y+1)%m; i != y; i= (i+1)%m) {
        if (M[row][i] == 0)
            continue;
        else
            M[x][i] += t*M[row][i];
    }
    M[x][y] = 0;
    return t;
}

/*
 *
 * Constructors and Destructors
 *
 */

Matrix::Matrix()
{
    n = 0;
    m = 0;
    M = NULL;

}

Matrix::Matrix(Matrix const &p) {
    unsigned int i, j;
    n = p.n;
    m = p.m;

    M = new double*[n];
    for (i = 0; i < n; i++) {
        M[i] = new double[m];
        for (j = 0; j < m; j++) {
            this->M[i][j] = p.M[i][j];
        }
    }
}

Matrix::Matrix(unsigned int a, unsigned int b)
{
    unsigned int i;

    if ((a == 0) || (b == 0)) {
        M = NULL;
        m = n = 0;
        return;
    }

    n = a;
    m = b;

    M = new double*[a];
    for (i = 0; i < n; i++)
        M[i] = new double[b];

}

Matrix::Matrix(double **d, unsigned int _n, unsigned int _m) {
    unsigned int i, j;
    n = _n;
    m = _m;

    M = new double*[n];
    for (i = 0; i < n; i++) {
        M[i] = new double[m];
        for (j = 0; j < m; j++)
            M[i][j] = d[i][j];
    }
}

Matrix::Matrix(double *d, unsigned int _n, unsigned int deg) {
    unsigned int i, j;
    n = _n;
    m = deg+1;

    M = new double*[n];
    for (i=0; i < n; i++){
        M[i] = new double[m];
        M[i][0] = 1;
        for (j=0; j < deg; j++) {
            M[i][j+1] = M[i][j]*d[i];
        }
    }
}

Matrix::~Matrix()
{
    this->delMat();
    M = NULL;
    n = 0;
    m = 0;
}


void Matrix::init(double **d, unsigned int _n,unsigned int _m) {
    unsigned int i, j;
    if (M){
        for (i = 0; i < n; i++){
            delete[] M[i];
        }
        delete[] M;
    }

    n = _n;
    m = _m;
    M = new double*[n];
    for (i = 0; i < n; i++) {
        M[i] = new double[m];
        for (j = 0; j < m; j++)
            M[i][j] = d[i][j];
    }
}


/*
 *
 * Operators
 *
 */

/*
 * Arithmetic Operators
 */

// Assignement Operators

Matrix& Matrix::operator=(const double d) {
    unsigned int i,j;

    for (i = 0; i < n; i++) {
        for (j =0; j<m; j++) {
            M[i][j] = d;
        }
    }
    return *this;
}

Matrix& Matrix::operator=(const Matrix &p) {
    unsigned int i,j;

    if (&p == this) {
        return *this;
    }

    if (M) {
        this->delMat();
    }
    n = p.n;
    m = p.m;

    M = new double*[n];
    for (i = 0; i < n; i++) {
        M[i] = new double[m];
        for (j = 0; j < m; j++) {
            this->M[i][j] = p.M[i][j];
        }
    }

    return *this;
}


// Addition

Matrix Matrix::operator+(const Matrix &p) {
    Matrix R;
    unsigned int i, j;

    if ((n != p.n)&&(m != p.m))
           return R;

    R = *this;

    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            R.M[i][j] += p.M[i][j];
        }
    }

    return R;
}


// Subtraction

Matrix Matrix::operator-(){
    unsigned int i, j;
    Matrix R(*this);

    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            R.M[i][j] = -R.M[i][j];
        }
    }

    return R;
}

Matrix Matrix::operator-(const double d){
    unsigned int i, j;
    Matrix R(*this);

    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            R.M[i][j] -= d;
        }
    }

    return R;
}

Matrix Matrix::operator-(const Matrix &p) {
    Matrix R;
    unsigned int i, j;

    if ((n != p.n)&&(m != p.m)) {
           return R;
    }
    R = *this;

    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            R.M[i][j] -= p.M[i][j];
        }
    }

    return R;
}

// Multiplication

Matrix Matrix::operator*(double a) {
    unsigned int i, j;
    Matrix R(*this);

    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            R.M[i][j] *= a;
        }
    }

    return R;
}

Matrix Matrix::operator*(const Matrix &p) {
    Matrix R;
    unsigned int i, j, k;

    if (this->m != p.n) {
           return R;
    }

    R.M = new double*[n];
    for (i = 0; i < this->n; i++) {
        R.M[i] = new double[p.m];
        for (j = 0; j < p.m; j++) {
            R.M[i][j] = 0;
            for (k = 0; k < this->m; k++) {
                R.M[i][j] += (M[i][k])*(p.M[k][j]);
            }
        }
    }
    R.n = n;
    R.m = p.m;

    return R;
}


VectorN Matrix::operator*(const VectorN& v){// returns the null vector if dimensions do not match
    VectorN ret;

    if (v.dim() != m)
        return ret;

    ret = v;
    ret *= *this;

    return ret;
}

/*
 *
 * Compound Operators
 *
 */

// Addition

Matrix& Matrix::operator+=(const Matrix &p) {
    unsigned int i, j;

    if ((this->n!=p.n)&&(this->m!=p.m)) {
        this->delMat();
        M = NULL;
        n = 0;
        m = 0;
        return *this;
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            M[i][j] += p.M[i][j];
        }
    }

    return *this;
}

Matrix& Matrix::operator-=(const Matrix &p) {
    unsigned int i, j;

    if ( (this->n!=p.n)||(this->m!=p.m)){
        this->delMat();
        M = NULL;
        n = 0;
        m = 0;
        return *this;
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            M[i][j] -= p.M[i][j];
        }
    }

    return *this;
}

Matrix& Matrix::operator*=(const double d) {
    unsigned int i, j;

    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            M[i][j] *= d;
        }
    }

    return *this;
}

Matrix& Matrix::operator*=(const Matrix &p) {
    unsigned int i, j, k;
    double **fng;

    if (this->m != p.n) {
        this->delMat();
        M = NULL;
        n = 0;
        m = 0;
        return *this;
    }

    fng = new double*[n];
    for (i = 0; i < this->n; i++) {
        fng[i] = new double[(p.m)];
        for (j = 0; j < p.m; j++) {
            fng[i][j] = 0;
            for (k = 0; k < this->m; k++) {
                fng[i][j] += (M[i][k])*(p.M[k][j]);
            }
        }
    }

    this->delMat();
    M = fng;
    this->m = p.m;

    return *this;
}


/*
 *
 * Bitwise Operators
 *
 */

std::ostream& operator<<(std::ostream& os, const Matrix& A) {
    unsigned int i, j;
    for (i = 0; i < A.n; i++) {
        os << "[ ";
        for (j = 0; j < A.m; j++) {
            os << A.M[i][j] << " ";
        }
        os << "]";
        if (i < A.n-1)
            os << std::endl;
    }

    if ( (A.n == 0) || (A.m == 0)) {
        os << "[]" << std::endl;
    }

    return os;
}

// Member and Pointer Operators

double* Matrix::operator[](unsigned int i) {
    return M[i];
}

/*
 *
 * Misc Functions
 *
 */

unsigned int Matrix::dimr() const{
    return n;
}

unsigned int Matrix::dimc() const{
    return m;
}

void Matrix::trans() {
    unsigned int i, j;
    double t;
    if (n == m) {
        for (i = 0; i < n; i++) {
            for (j = 0; j < i; j++) {
                t = M[i][j];
                M[i][j] = M[j][i];
                M[j][i] = t;
            }
        }
    }
    else {
        double **T;
        T = new double*[m];
        for (i = 0; i < m; i++)
            T[i] = new double[n];

        for (i = 0; i < n; i++)
            for (j = 0; j < m; j++)
                T[j][i] = M[i][j];

        for (i = 0; i < n; i++)
            delete[] M[i];

        delete[] M;
        SWAP(n, m);
        M = T;
    }
}

void Matrix::iden() {
    unsigned int i, j;

    for (i = 0; i < n; i++){
        for (j = 0; j < m; j++) {
            if (j == i)
                M[i][j] = 1;
            else
                M[i][j] = 0;
        }
    }
}

void Matrix::zero() {
    unsigned int i, j;
    for (i = 0; i < n; i++)
        for (j=0; j<m; j++)
            M[i][j] = 0;
}

double Matrix::det() {
    int temp[n], sgn = 1;
    unsigned int i;
    double ret=0, term;
    for (i = 0; i < n; i++) temp[i] = i;
    sequence col(SEQT_PERM, temp, n, n);

    do {
        for (term = 1, i = 0; i < n; i++)
            term *= M[i][col[i]];
        ret += sgn*term;
        sgn *= -1;

    }while(col.next());

    return ret;
}

void Matrix::swpRow(unsigned int x, unsigned int y) {
    double t;
    if (x == y)
       return;
    for (unsigned int i = 0; i < m; i++) {
        t = M[x][i];
        M[x][i] = M[y][i];
        M[y][i] = t;
    }
}

void Matrix::mulRow(double a, unsigned int x) {
    for (unsigned int i=0; i<m; i++)
        (M[x][i]) *= a;

}

void Matrix::addLinMul(double a, unsigned int x, unsigned int y) {
    if (x == y)
        return;
    for (unsigned int i=0; i<m; i++)
        M[y][i] += a*M[x][i];
}


void Matrix::rref() {
    unsigned int i, j;

    for (i = 0; i < n; i++) {

        // check if M[i][i] is nonzero
        if (M[i][i] == 0) {
            for (j = i+1; j < n; j++) {
                // find a row with nonzero entry at M[*][i]
                if (M[j][i] != 0){
                    this->swpRow(j,i);
                    break;
                }
            }
            if (j == n) // our work is kinda already done for us
                continue;
        }

        // for each entry below it,
        for (j = i+1; j < n; j++) {
            // zero out that element by adding a linear multiple
            zeroOnIndex(i, j, i);
        }
    }

    // go backwards
    for (i = n-1; i < n; i--) {
        if (M[i][i] == 0)
            continue;
        for (j = i-1; j < n; j--) {
            zeroOnIndex(i, j, i);
        }
    }

    // make everything ones
    for (i = 0; i < n; i++) {
        if (M[i][i] != 0)
            this->mulRow(1/M[i][i], i);
    }
}

void Matrix::rref(VectorN &sol) {
    unsigned int i, j;
    double t;

    for (i = 0; i < n; i++) {

        // check if M[i][i] is nonzero
        if (M[i][i] == 0) {
            for (j = i+1; j < n; j++) {
                // find a row with nonzero entry at M[*][i]
                if (M[j][i] != 0){
                    this->swpRow(j,i);
                    t = sol[j];
                    sol[j] = sol[i];
                    sol[i] = t;
                    break;
                }
            }
            if (j == n) // our work is kinda already done for us
                continue;
        }

        // for each entry below it,
        for (j = i+1; j < n; j++) {
            // zero out that element by adding a linear multiple
            sol[j] += sol[i] * zeroOnIndex(i, j, i);
        }
    }

    // go backwards
    for (i = n-1; i < n; i--) {
        if (M[i][i] == 0)
            continue;
        for (j = i-1; j < n; j--) {
            sol[j] += sol[i] * zeroOnIndex(i, j, i);
        }
    }

    // make everything ones
    for (i = 0; i < n; i++) {
        if (M[i][i] != 0) {
            t = 1/M[i][i];
            sol[i] *= t;
            this->mulRow(t, i);
        }
    }
}

Matrix Matrix::inv() {
    double t;
    unsigned int i, j;
    Matrix cpy(*this), ret(n,m);
    ret.iden();

    for (i = 0; i < n; i++) {

        // check if M[i][i] is nonzero
        if (cpy.M[i][i] == 0) {
            for (j = i+1; j < n; j++) {
                // find a row with nonzero entry at M[*][i]
                if (cpy.M[j][i] != 0){
                    cpy.swpRow(j,i);
                    ret.swpRow(j,i);
                    break;
                }
            }
            if (j == n) // our work is kinda already done for us
                continue;
        }

        // for each entry below it,
        for (j = i+1; j < n; j++) {
            // zero out that element by adding a linear multiple
            ret.addLinMul(cpy.zeroOnIndex(i, j, i), i, j);
        }
    }

    // go backwards
    for (i = n-1; i < n; i--) {
        if (cpy.M[i][i] == 0)
            continue;
        for (j = i-1; j < n; j--) {
            ret.addLinMul(cpy.zeroOnIndex(i, j, i), i, j);
        }
    }

    // make everything ones
    for (i = 0; i < n; i++) {
        if (cpy.M[i][i] != 0) {
            t = 1/cpy.M[i][i];
            cpy.mulRow(t, i);
            ret.mulRow(t, i);
        }
    }

    return ret;
}

void Matrix::resz(unsigned int a, unsigned int b) {
    unsigned int i;
    n = a;
    m = b;

    if (M) {
        this->delMat();
    }
    if ((a == 0) || (b == 0)) {
        M = NULL;
        n = 0;
        m = 0;
        return;
    }

    M = new double*[n];
    for (i = 0; i < n; i++) {
        M[i] = new double[m];
    }
}


/*
 *
 * Global Operators
 *
 */

Matrix operator*(const double& d, const Matrix &p) {
    Matrix R = p;
    R *= d;

    return R;
}

/*
 *
 * Matrix Algorithms
 *
 */

VectorN LstSqApprox(double *X, double *Y, unsigned int n, unsigned int deg) {
    VectorN sol(Y, n);
    Matrix mat(X, n, deg), matT(mat);

    matT.trans();
    // cout << mat << endl << endl;
    // cout << matT << endl;
    // cout << sol << endl << endl;

    sol *= matT;
    // cout << sol << endl;

    matT *= mat;
    // cout << matT << endl << endl;

    matT.rref(sol);

    // cout << matT << endl << endl;

    return sol;
}

