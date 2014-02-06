#ifndef MATRIX4_H
#define MATRIX4_H

// Designed to be used with opengl
// therefore this is a column major saved matrix
// TODO Optimize by unrolling
class Matrix4
{
private:
    double M[4][4];
public:
    Matrix4();
    Matrix4(const double a);// creates the a * the indentity matrix
    Matrix4(const Matrix4&);// copy constructor
    Matrix4(double d[][4]); // copy from a 3x* double array
    Matrix4(double **d); // copy from dynamic array

    void init(double d[][4]);// initialize with static memory
    void init(double **d);// initialize with dynamic memory, must be *d[3]

    Matrix4& operator=(const double d); // assign d to every entry
    Matrix4& operator=(const Matrix4&); // deep copy
    Matrix4 operator+(const Matrix4&);// add two 3d matricies
    Matrix4 operator-(const Matrix4&);// subtract two 3d matricies
    Matrix4 operator*(const double d);// multiply each entry by d
    Matrix4 operator/(const double d);// multiply each entry by d
    Matrix4 operator*(const Matrix4 &A);// matrix multiplication, executed as (*this)*(A)

    // Compound Operators
    Matrix4& operator+=(const Matrix4&);// matrix addition
    Matrix4& operator-=(const Matrix4&);// matrix subtraction
    Matrix4& operator*=(const double);// matrix multiplication
    Matrix4& operator*=(const Matrix4&);// matrix addition

    // Stream Operators
    friend std::ostream& operator<<(std::ostream&, const Matrix4&);

    // Accessor Function
    double* operator[](unsigned int);

    // Misc Operations
    void trans();
    void iden();
    void zero();
    double det();
    Matrix4 inv(); // r
};

#endif // MATRIX4_H
