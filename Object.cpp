#include <GL/glu.h>
#include <GL/gl.h>
#include "Object.h"
#include <stdio.h>

Object::Object(){
    vec = new Vec2(0,0);
    verts[0] = 0;
    verts[1] = 0;
    verts[2] = 100;
    verts[3] = 0;
    verts[4] = 50;
    verts[5] = 100;
}

Object::~Object(){
}

void Object::draw(){
/*
    Place Holder Draw Function, Will be replaced with Rectangles and Textures Later
*/
    glBegin(GL_TRIANGLES);
        glColor3f(0,1,0);
        glVertex3f(verts[0],verts[1],0);
        glColor3f(1,0,0);
        glVertex3f(verts[2],verts[3],0);
        glColor3f(0,0,1);
        glVertex3f(verts[4],verts[5],0);
    glEnd();
}

void Object::addForce(Vec2 *pvec)
{
    vec->add(pvec->getx(), pvec->gety());
}

void Object::moveobj(int dir){
    int dx = vec->getx();
    int dy = vec->gety();
    verts[0] += dx;
    verts[2] += dx;
    verts[4] += dx;
    verts[1] += dy;
    verts[3] += dy;
    verts[5] += dy;
    //printf("%d\n", dir);
//    switch(dir)
//    {
//    case 1:
//        verts[0] -= 6;
//        verts[2] -= 6;
//        verts[4] -= 6;
//        break;
//    case 2:
//        //x
//        verts[0] -= 4;
//        verts[2] -= 4;
//        verts[4] -= 4;
//        //y
//        verts[1] -= 4;
//        verts[3] -= 4;
//        verts[5] -= 4;
//        break;
//    case 3:
//        verts[1] -= 6;
//        verts[3] -= 6;
//        verts[5] -= 6;
//        break;
//    case 4:
//        //x
//        verts[0] += 4;
//        verts[2] += 4;
//        verts[4] += 4;
//        //y
//        verts[1] -= 4;
//        verts[3] -= 4;
//        verts[5] -= 4;
//        break;
//    case 5:
//        verts[0] += 6;
//        verts[2] += 6;
//        verts[4] += 6;
//        break;
//    case 6:
//        //x
//        verts[0] += 4;
//        verts[2] += 4;
//        verts[4] += 4;
//        //y
//        verts[1] += 4;
//        verts[3] += 4;
//        verts[5] += 4;
//        break;
//    case 7:
//        //y
//        verts[1] += 6;
//        verts[3] += 6;
//        verts[5] += 6;
//        break;
//    case 8:
//        //x
//        verts[0] -= 4;
//        verts[2] -= 4;
//        verts[4] -= 4;
//        //y
//        verts[1] += 4;
//        verts[3] += 4;
//        verts[5] += 4;
//        break;
//    default:
//        break;
//    }
}
