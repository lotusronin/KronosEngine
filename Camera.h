#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>
#include <GL/gl.h>
#include "Matrix.h"

class Camera{
protected:
    float x, y;
    TranslationMatrix* pCameraTransform;
public:
    Camera(float a, float b);
    void UpdateView(float dx, float dy);
    TranslationMatrix* GetTransform();
};

#endif
