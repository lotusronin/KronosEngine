#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>
#include <GL/gl.h>
#include "Matrix.h"

class Camera{
protected:
    float x, y;
    Matrix* pCameraTransform;
public:
    Camera(float a, float b);
    ~Camera();
    void UpdateView(float dx, float dy);
    Matrix* GetTransform();
};

#endif
