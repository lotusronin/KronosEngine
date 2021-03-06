#include "Camera.h"
#include <GL/glew.h>
#include <GL/gl.h>
#include <iostream>

Camera::Camera(float a, float b) : x(a), y(b)
{
    pCameraTransform = new Matrix();
}

void Camera::UpdateView(float dx, float dy)
{
    float diffx = x - dx;
    x -= diffx;
    float diffy = y - dy;
    y -= diffy;

    Matrix temp = Matrix();
    temp.setTranslation(diffx, diffy, 0.0f);
    //pCameraTransform->SetTranslation(diffx, diffy, 0.0f);
    (*pCameraTransform) = (*pCameraTransform)*temp;
    //glMatrixMode (GL_MODELVIEW);
    //glTranslatef(diffx, diffy, 0);
}

Matrix* Camera::GetTransform()
{
    return pCameraTransform;
}
