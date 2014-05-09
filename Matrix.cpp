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
{}

RotationMatrix::RotationMatrix() : Matrix()
{}

RotationMatrix::~RotationMatrix()
{}

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
