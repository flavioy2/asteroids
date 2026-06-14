#include "Shape.h"

#ifndef __OVNI_H__
#define __OVNI_H__

class Ovni : public Shape {
private:
    int size;
public:
    Ovni(int t);
    void draw();
    void move();
    float getSize();
    float operator+(Shape*);
    int temporizador;
    int estado;
};

#endif
