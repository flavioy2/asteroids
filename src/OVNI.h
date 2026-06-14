#include "Shape.h"

#ifndef __OVNI_H__
#define __OVNI_H__

class OVNI : public Shape {
private:
    int size;
public:
    OVNI(int t);
    void draw();
    void move();
    float getSize();
    float operator+(Shape*);
    int temporizador;
    int estado;
};

#endif