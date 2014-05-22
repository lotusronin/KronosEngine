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

   void setTranslation(float x, float y, float z);
   void setScale(float x, float y, float z);
   void setIdentity();
};

#endif // MATRIX_H
