#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>
#include <GL/gl.h>

class Camera{
protected:
    int x, y;
public:
    Camera(int a, int b);
    void UpdateView(int dx, int dy);

};

#endif
