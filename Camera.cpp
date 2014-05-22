#include "Camera.h"
#include <GL/glew.h>
#include <GL/gl.h>
#include <iostream>

Camera::Camera(float a, float b) : x(a), y(b)
{
    pCameraTransform = new TranslationMatrix();
}

void Camera::UpdateView(float dx, float dy)
{
    float diffx = x - dx;
    x -= diffx;
    float diffy = y - dy;
    y -= diffy;

    TranslationMatrix temp = TranslationMatrix(diffx, diffy, 0.0f);
    //pCameraTransform->SetTranslation(diffx, diffy, 0.0f);
    (*pCameraTransform) = (*pCameraTransform)*temp;
    //glMatrixMode (GL_MODELVIEW);
    //glTranslatef(diffx, diffy, 0);
}

TranslationMatrix* Camera::GetTransform()
{
    return pCameraTransform;
}
