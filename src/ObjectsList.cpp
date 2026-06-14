#include "ObjectsList.h"

ObjectsList::ObjectsList() {
    n = 0;
    head = NULL;

    theShippa = new Ship();
    add(theShippa);

    theOvni = NULL;
    tiempoOVNI = 0;

    for (int i = 0; i < NUMASTEROIDS; i++) {
        add(new Asteroid(RAND_DOM(1, 3)));
    }
}

void ObjectsList::add(Shape* s) {
    nodo* nuevo = new nodo();
    nuevo->obj = s;
    nuevo->next = head;
    head = nuevo;
    n++;
}

void ObjectsList::remove(Shape* s) {
    if (s == NULL) return;

    nodo* actual = head;
    nodo* anterior = NULL;

    while (actual != NULL) {
        if (actual->obj == s) {
            if (anterior == NULL)
                head = actual->next;
            else
                anterior->next = actual->next;
            delete actual;
            n--;
            return;
        }
        anterior = actual;
        actual = actual->next;
    }
}       

void ObjectsList::move() {
    tiempoOVNI++;
    if (tiempoOVNI > 1500 && theOvni == NULL) {
        theOvni = new Ovni(1);
        add(theOvni);
        tiempoOVNI = 0;
    }

    nodo* actual = head;
    while (actual != NULL) {
        actual->obj->move();
        actual = actual->next;
    }
}

void ObjectsList::draw() {
    nodo* actual = head;
    while (actual != NULL) {
        actual->obj->draw();
        actual = actual->next;
    }
}

Ship* ObjectsList::getShip() {
    return theShippa;
}

void ObjectsList::reposition(Ship* ship) {
    nodo* actual = head;
    while (actual != NULL) {
        Asteroid* asteroid = dynamic_cast<Asteroid*>(actual->obj);
        if (asteroid != NULL) {
            float apos[3];
            asteroid->getPos(apos);
            if (mydistance(apos[X], apos[Y], 0, 0) < 2 * asteroid->getSize())
                asteroid->reposition();
        }
        actual = actual->next;
    }
    theShippa = ship;
    add(theShippa);
}

int ObjectsList::collisions(Bullet* bullet, Ship* ship, float* expl_pos) {
    nodo* actual = head;
    while (actual != NULL) {
        Asteroid* asteroid = dynamic_cast<Asteroid*>(actual->obj);
        if (asteroid != NULL) {
            if (ship != NULL) {
                float spos[3];
                ship->getPos(spos);
                if ((*asteroid + ship) < asteroid->getSize() + ship->getSize()) {
                    expl_pos[X] = spos[X];
                    expl_pos[Y] = spos[Y];
                    remove(ship);
                    theShippa = NULL;
                    return 1;
                }
            }
            if (bullet != NULL) {
                float apos[3];
                asteroid->getPos(apos);
                if ((*asteroid + bullet) < asteroid->getSize() + bullet->getSize()) {
                    expl_pos[X] = apos[X];
                    expl_pos[Y] = apos[Y];
                    remove(bullet);
                    if (asteroid->getSize() == SMALL * 0.3f) {
                        remove(asteroid);
                        return 4;
                    }
                    else {
                        Asteroid* nuevo = asteroid->split();
                        add(nuevo);
                        if (asteroid->getSize() == MEDIUM * 0.3f) return 2;
                        else return 3;
                    }
                }
            }
        }
        Ovni* ovni = dynamic_cast<Ovni*>(actual->obj);
        if (ovni != NULL && bullet != NULL) {
            if ((*ovni + bullet) < ovni->getSize() + bullet->getSize()) {
                remove(bullet);
                remove(ovni);
                theOvni = NULL;
                tiempoOVNI = 0;   // <-- aqui
                if (ovni->getSize() == BIG * 0.3) return 7;
                if (ovni->getSize() == MEDIUM * 0.3) return 6;
                return 5;
            }
        }
        actual = actual->next;
    }
    return 0;
}

ObjectsList::~ObjectsList() {
    nodo* actual = head;
    while (actual != NULL) {
        nodo* siguiente = actual->next;
        delete actual->obj;
        delete actual;
        actual = siguiente;
    }
}
