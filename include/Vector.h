#ifndef VECTOR_H
#define VECTOR_H

class Vec2{
private:
    // positive y is down the screen
    int x, y;
public:
    Vec2(int a, int b);
    int getx();
    int gety();
    void negx();
    void negy();
    void zeroy();
    void zerox();
    void add(int a, int b);
};

#endif
