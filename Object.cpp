#include <GL/glu.h>
#include <GL/gl.h>
#include "Object.h"
#include <stdio.h>
#include <FreeImage.h>

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
    onground = false;
}

MobileObject::~MobileObject(){
    delete vec;
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

void MobileObject::moveobj(){
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
}

void MobileObject::setonground(bool b){
onground = b;
}

bool MobileObject::isonground(){
return onground;
}

int MobileObject::getCenterX(){
return (verts[2] - verts[0])/2 + verts[0];
}

int MobileObject::getCenterY(){
return (verts[5] - verts[3])/2 + verts[3];
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
    delete vec;
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

void Object::setTexture(FIBITMAP* img){
    texture = img;
}
