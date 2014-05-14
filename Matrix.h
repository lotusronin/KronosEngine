#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

class Matrix
{
public:
    float mat[16];
   Matrix();
   virtual ~Matrix();
   Matrix operator*(const Matrix& other);
   Matrix operator+(const Matrix& other);
   Matrix operator=(const Matrix& other);
};

class RotationMatrix: public Matrix
{
public:
    RotationMatrix();
    ~RotationMatrix();
};

class ScaleMatrix: public Matrix
{
public:
    ScaleMatrix();
    ScaleMatrix(float x, float y, float z);
    ~ScaleMatrix();
};

class TranslationMatrix: public Matrix
{
public:
    TranslationMatrix();
    TranslationMatrix(float x, float y, float z);
    void SetTranslation(float x, float y, float z);
    ~TranslationMatrix();
    TranslationMatrix operator*(const Matrix& other);
    TranslationMatrix operator+(const Matrix& other);
    TranslationMatrix operator=(const Matrix& other);
};

class OrthoMatrix: public Matrix
{
public:
    OrthoMatrix();
    ~OrthoMatrix();
};
#endif // MATRIX_H
