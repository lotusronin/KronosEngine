#include <GL/glu.h>
#include <GL/gl.h>
#include "Object.h"
#include <stdio.h>

MobileObject::MobileObject(){
    vec = new Vec2(0,0);
    verts[0] = 0;
    verts[1] = 0;
    verts[2] = 64;
    verts[3] = 0;
    verts[4] = 64;
    verts[5] = 64;
    verts[6] = 0;
    verts[7] = 64;
}

MobileObject::~MobileObject(){
}

Vec2* MobileObject::getSpeed(){
    return vec;
}

int* MobileObject::getVerts(){
    return verts;
}

void MobileObject::draw(){
/*
    Place Holder Draw Function, Will be replaced with Rectangles and Textures Later
*/
    glBegin(GL_QUADS);
        glColor3f(0,1,0);
        glVertex3f(verts[0],verts[1],0);
        glColor3f(1,0,0);
        glVertex3f(verts[2],verts[3],0);
        glColor3f(0,0,1);
        glVertex3f(verts[4],verts[5],0);
        glColor3f(1,1,1);
        glVertex3f(verts[6],verts[7],0);
    glEnd();
}

void MobileObject::addForce(Vec2 *pvec)
{
    vec->add(pvec->getx(), pvec->gety());
}

void MobileObject::stop(bool x, bool y){
if(x){
    vec->zerox();
}
if(y){
    vec->zeroy();
}
}

void MobileObject::moveobj(int dir){
    int dx = vec->getx();
    int dy = vec->gety();
    verts[0] += dx;
    verts[2] += dx;
    verts[4] += dx;
    verts[6] += dx;
    verts[1] += dy;
    verts[3] += dy;
    verts[5] += dy;
    verts[7] += dy;

    //printf("%d\n", dir);
//    switch(dir)
//    {
//    case 1:
//        verts[0] -= 6;
//        verts[2] -= 6;
//        verts[4] -= 6;
//        break;
//    case 3:
//        verts[1] -= 6;
//        verts[3] -= 6;
//        verts[5] -= 6;
//        break;
//    case 5:
//        verts[0] += 6;
//        verts[2] += 6;
//        verts[4] += 6;
//        break;
//    case 7:
//        //y
//        verts[1] += 6;
//        verts[3] += 6;
//        verts[5] += 6;
//        break;
//    default:
//        break;
//    }
}

Object::Object(){
    vec = new Vec2(0,0);
    verts[0] = 0;
    verts[1] = 200;
    verts[2] = 100;
    verts[3] = 200;
    verts[4] = 100;
    verts[5] = 300;
    verts[6] = 0;
    verts[7] = 300;
}

Object::~Object(){

}

int* Object::getVerts(){
    return verts;
}

Vec2* Object::getSpeed(){
    Vec2* v = new Vec2(0,0);
    return v;
}

void Object::draw(){
/*
    Place Holder Draw Function, Will be replaced with Rectangles and Textures Later
*/
    glBegin(GL_QUADS);
        glColor3f(0,.5,0);
        glVertex3f(verts[0],verts[1],0);
        glVertex3f(verts[2],verts[3],0);
        glColor3f(.55,.27,.07);
        glVertex3f(verts[4],verts[5],0);
        glVertex3f(verts[6],verts[7],0);
    glEnd();
}
