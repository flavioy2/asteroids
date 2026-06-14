#include "commonstuff.h"
#include "OVNI.h"

OVNI::OVNI(int t)
{
    size = RAND_DOM(1, 3);
    pos[X] = -SIZEX2;
    pos[Y] = RAND_DOMF(-SIZEY2, SIZEY2);
    pos[Z] = 0;
    tspeed[X] = OVNI_SPEED;
    tspeed[Y] = 0;
    tspeed[Z] = 0;
    rot[X] = 0;
    rot[Y] = 0;
    rot[Z] = 0;
    rspeed[X] = 0;
    rspeed[Y] = 0;
    rspeed[Z] = 0;
    color[R] = 1.0;
    color[G] = 0.78;
    color[B] = 0.0;
    temporizador = 0;
}

void OVNI::draw() {
    predraw();
    glutSolidTorus(size * 0.1, size * 0.3, 9, 8);
    postdraw();
}

void OVNI::move() {
    temporizador++;
    pos[X] += tspeed[X];

    if (temporizador > RAND_DOM(500, 1000)) {
        tspeed[Y] = RAND_DOMF(-0.03, 0.03);
        temporizador = 0;
    }

    pos[Y] += tspeed[Y];

    if (pos[X] > SIZEX2) pos[X] = -SIZEX2;
    if (pos[X] < -SIZEX2) pos[X] = SIZEX2;
    if (pos[Y] >= SIZEY2) {
        pos[Y] = SIZEY2;
        tspeed[Y] = 0;
    }
    if (pos[Y] <= -SIZEY2) {
        pos[Y] = -SIZEY2;
        tspeed[Y] = 0;
    }
}

float OVNI::getSize() {
    return (size * 0.3);
}

float OVNI::operator+(Shape* s) {
    float p[3];
    s->getPos(p);
    return mydistance(pos[X], pos[Y], p[X], p[Y]);
}
