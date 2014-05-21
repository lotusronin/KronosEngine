#include "Camera.h"
#include <GL/glew.h>
#include <GL/gl.h>
#include <iostream>

Camera::Camera(int a, int b)
{
    x = a;
    y = b;
}

void Camera::UpdateView(int dx, int dy)
{
    float diffx = x - dx;
    x -= diffx;
    float diffy = y - dy;
    y -= diffy;
    //glMatrixMode (GL_MODELVIEW);
    glTranslatef(diffx, diffy, 0);
}
