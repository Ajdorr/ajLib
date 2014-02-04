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

vectorn::vectorn(){
    V = NULL;
    n = 0;
}

vectorn::vectorn(const vectorn &v) {
    n = v.n;
    V = new double[n];
    for (unsigned int i = 0; i < v.n; i++)
        V[i] = v.V[i];
}

vectorn::vectorn(double *_v, unsigned int _n){
    n = _n;
    V = new double[n];
    for (unsigned int i = 0; i < _n; i++)
        V[i] = _v[i];
}

vectorn::~vectorn() {
    if (V)
        delete[] V;
    n = 0;
}

vectorn& vectorn::operator=(const vectorn &v) {
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
vectorn vectorn::operator+(const vectorn &v) {
    vectorn ng;
    if (v.n != n)
        return ng;

    ng.n = n;
    ng.V = new double[n];

    for (unsigned int i = 0; i < n; i++)
        ng.V[i] = V[i] + v.V[i];

    return ng;
}

vectorn vectorn::operator-(const vectorn &v){
    vectorn ng;
    if (v.n != n)
        return ng;

    ng.n = n;
    ng.V = new double[n];

    for (unsigned int i = 0; i < n; i++)
        ng.V[i] = V[i] - v.V[i];

    return ng;
}

vectorn& vectorn::operator+=(const vectorn &v) {
    if (v.n != n)
        return *this;

    for (unsigned int i = 0; i < n; i++)
        V[i] += v.V[i];

    return *this;
}


vectorn& vectorn::operator-=(const vectorn &v){
    if (v.n != n)
        return *this;

    for (unsigned int i = 0; i < n; i++)
        V[i] -= v.V[i];

    return *this;
}

vectorn& vectorn::operator*=(const matrix &A) {
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


double vectorn::operator*(const vectorn &v) {
    double ret = 0;
    if (v.n != n)
        return ret;

    for (unsigned int i = 0; i < n; i++)
        ret += V[i] * v.V[i];

    return ret;
}


// Scalar argumented operations
vectorn vectorn::operator*(const double a) {
    vectorn ng(*this);

    ng *=a;

    return ng;
}

vectorn vectorn::operator/(const double a) {
    vectorn ng(*this);

    ng *= 1/a;

    return ng;
}

// Compound Operations
vectorn& vectorn::operator*=(const double a) {
    for (unsigned int i = 0; i < n; i++)
        V[i] *= a;

    return *this;
}

vectorn& vectorn::operator/=(const double a){
    *this *= 1/a;

    return *this;
}

// Accessibility Operators
double& vectorn::operator[](const int i) {
    return V[i];
}

std::ostream& operator<<(std::ostream &os, const vectorn &v){
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

unsigned int vectorn::dim() const {
    return n;
}

vectorn vectorn::unit() {
    vectorn ng;
    double mg = this->mag();
    if (mg == 0)
        return ng;

    ng = *this;
    ng /= mg;

    return ng;
}

double vectorn::mag() {
    double ret = 0;
    for (unsigned int i = 0; i < n; i++)
        ret += V[i]*V[i];

    return sqrt(ret);
}

void vectorn::zero(){
    for (unsigned int i = 0; i < n; i++)
        V[i] = 0;

}

vectorn operator*(const double &a, const vectorn &v) {
    vectorn ng(v);
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

void matrix::delMat() {
    unsigned int i;

    for (i = 0; i < n; i++)
        delete[] M[i];
    delete[] M;
}

// using row zero out index (x,y)
// returns the multiplication factor
double matrix::zeroOnIndex(unsigned int row, unsigned int x, unsigned int y) {
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

matrix::matrix()
{
    n = 0;
    m = 0;
    M = NULL;

}

matrix::matrix(matrix const &p) {
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

matrix::matrix(unsigned int a, unsigned int b)
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

matrix::matrix(double **d, unsigned int _n, unsigned int _m) {
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

matrix::matrix(double *d, unsigned int _n, unsigned int deg) {
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

matrix::~matrix()
{
    this->delMat();
    M = NULL;
    n = 0;
    m = 0;
}


void matrix::init(double **d, unsigned int _n,unsigned int _m) {
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

matrix& matrix::operator=(const double d) {
    unsigned int i,j;

    for (i = 0; i < n; i++) {
        for (j =0; j<m; j++) {
            M[i][j] = d;
        }
    }
    return *this;
}

matrix& matrix::operator=(const matrix &p) {
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

matrix matrix::operator+(const matrix &p) {
    matrix R;
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

matrix matrix::operator-(){
    unsigned int i, j;
    matrix R(*this);

    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            R.M[i][j] = -R.M[i][j];
        }
    }

    return R;
}

matrix matrix::operator-(const double d){
    unsigned int i, j;
    matrix R(*this);

    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            R.M[i][j] -= d;
        }
    }

    return R;
}

matrix matrix::operator-(const matrix &p) {
    matrix R;
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

matrix matrix::operator*(double a) {
    unsigned int i, j;
    matrix R(*this);

    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            R.M[i][j] *= a;
        }
    }

    return R;
}

matrix matrix::operator*(const matrix &p) {
    matrix R;
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


vectorn matrix::operator*(const vectorn& v){// returns the null vector if dimensions do not match
    vectorn ret;

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

matrix& matrix::operator+=(const matrix &p) {
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

matrix& matrix::operator-=(const matrix &p) {
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

matrix& matrix::operator*=(const double d) {
    unsigned int i, j;

    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            M[i][j] *= d;
        }
    }

    return *this;
}

matrix& matrix::operator*=(const matrix &p) {
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

std::ostream& operator<<(std::ostream& os, const matrix& A) {
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

double* matrix::operator[](unsigned int i) {
    return M[i];
}

/*
 *
 * Misc Functions
 *
 */

unsigned int matrix::dimr() const{
    return n;
}

unsigned int matrix::dimc() const{
    return m;
}

void matrix::trans() {
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

void matrix::iden() {
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

void matrix::zero() {
    unsigned int i, j;
    for (i = 0; i < n; i++)
        for (j=0; j<m; j++)
            M[i][j] = 0;
}

double matrix::det() {
    int temp[n], sgn = 1;
    unsigned int i;
    double ret=0, term;
    sequence col;

    for (i = 0; i < n; i++)
        temp[i] = i;

    col.init(SEQT_PERM, temp, n, n);

    do {
        for (term = 1, i = 0; i < n; i++)
            term *= M[i][col[i]];
        ret += sgn*term;
        sgn *= -1;

    }while(col.next());

    return ret;
}

void matrix::swpRow(unsigned int x, unsigned int y) {
    double t;
    if (x == y)
       return;
    for (unsigned int i = 0; i < m; i++) {
        t = M[x][i];
        M[x][i] = M[y][i];
        M[y][i] = t;
    }
}

void matrix::mulRow(double a, unsigned int x) {
    for (unsigned int i=0; i<m; i++)
        (M[x][i]) *= a;

}

void matrix::addLinMul(double a, unsigned int x, unsigned int y) {
    if (x == y)
        return;
    for (unsigned int i=0; i<m; i++)
        M[y][i] += a*M[x][i];
}


void matrix::rref() {
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

void matrix::rref(vectorn &sol) {
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

matrix matrix::inv() {
    double t;
    unsigned int i, j;
    matrix cpy(*this), ret(n,m);
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

void matrix::resz(unsigned int a, unsigned int b) {
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

matrix operator*(const double& d, const matrix &p) {
    matrix R = p;
    R *= d;

    return R;
}

/*
 *
 * Matrix Algorithms
 *
 */

vectorn LstSqApprox(double *X, double *Y, unsigned int n, unsigned int deg) {
    vectorn sol(Y, n);
    matrix mat(X, n, deg), matT(mat);

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

