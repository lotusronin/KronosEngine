#include "Matrix.h"
#include <math.h>

/*
*   A Set of classes to describe some basic matrices.
*   Matrices are column-major for ease of use with GLSL.
*/

Matrix::Matrix() : mat{0}
{
    mat[0] = 1;
    mat[5] = 1;
    mat[10] = 1;
    mat[15] = 1;
}

Matrix::~Matrix()
{
    std::cout << "Matrix Deconstructor called!!\n";
}


/*
*   Operator overloading for matrix multiplication and addition.
*/

Matrix Matrix::operator*(const Matrix& other)
{
    Matrix temp = Matrix();
    for(int j = 0; j < 4; j++){
        for(int i = 0; i < 16; i += 4)
        {
            temp.mat[j+i] = mat[j]*other.mat[i]+mat[j+4]*other.mat[i+1]+mat[j+8]*other.mat[i+2]+mat[j+12]*other.mat[i+3];
        }
    }

    return temp;

}

Matrix Matrix::operator+(const Matrix& other)
{
    Matrix temp = Matrix();
    for(int i = 0; i < 16; i++)
    {
        temp.mat[i] = mat[i] + other.mat[i];
    }
    return temp;
}

Matrix Matrix::operator=(const Matrix& other)
{
    for(int i = 0; i < 16; i++)
    {
        mat[i] = other.mat[i];
    }
    return *this;
}

/*
*   RotationMatrix Definitions
*
*/

RotationMatrix::RotationMatrix() : Matrix()
{}

RotationMatrix::~RotationMatrix()
{}

/*
*   ScaleMatrix Definitions
*
*/

ScaleMatrix::ScaleMatrix() : Matrix()
{}

ScaleMatrix::ScaleMatrix(float x, float y, float z) : Matrix()
{
    mat[0] = x;
    mat[5] = y;
    mat[10] = z;
    mat[15] = 1;
}

ScaleMatrix::~ScaleMatrix()
{}

TranslationMatrix::TranslationMatrix() : Matrix()
{}

TranslationMatrix::TranslationMatrix(float x, float y, float z) : Matrix()
{
    mat[12] = x;
    mat[13] = y;
    mat[14] = z;
}

TranslationMatrix::~TranslationMatrix()
{
}

OrthoMatrix::OrthoMatrix() : Matrix()
{
}

OrthoMatrix::~OrthoMatrix(){}
