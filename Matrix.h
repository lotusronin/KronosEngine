#ifndef MATRIX_H
#define MATRIX_H

class Matrix
{
public:
    float mat[16];
   Matrix();
   virtual ~Matrix();
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
    ~TranslationMatrix();
};

class OrthoMatrix: public Matrix
{
public:
    OrthoMatrix();
    ~OrthoMatrix();
};
#endif // MATRIX_H
