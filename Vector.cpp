#include "Vector.h"

Vec2::Vec2(int a, int b){
x = a;
y = b;
}

int Vec2::getx(){
return x;
}

int Vec2::gety(){
return y;
}

void Vec2::add(int a, int b){
x += a;
y += b;
}
