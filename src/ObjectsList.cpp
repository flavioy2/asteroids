#include "ObjectsList.h"
#include "commonstuff.h"
ObjectsList::ObjectsList() {
    n = 0;
    head = NULL;
    theShippa = new Ship();
    add(theShippa);

    for (int i = 0; i < 1; i++) {
        add(new Asteroid(BIG));
    }
    reposition(theShippa);
}

void ObjectsList::move() {
    nodo* aux = head;

    while (aux != NULL) {
        aux->obj->move();
        aux = aux->next;
    }
}    
void ObjectsList::draw() {
    nodo* aux = head;

    while (aux != NULL) {
        aux->obj->draw();
        aux = aux->next;
    }
}

void ObjectsList::add(Shape* s) {
    nodo* nuevo = new nodo;
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

            if (anterior == NULL) {
                head = actual->next;
            }
            else {
                anterior->next = actual->next;
            }

            delete actual->obj;
            delete actual;
            n--;
            return;
        }

        anterior = actual;
        actual = actual->next;
    }
}

Ship* ObjectsList::getShip() {
    return theShippa;
}

int ObjectsList::collisions(Bullet* b, Ship* s, float* expl_pos) {
    nodo* aux = head;
    while (aux != NULL) {
        Asteroid* ast = dynamic_cast<Asteroid*>(aux->obj);

        if (ast != NULL) {

            // ASTEROIDE CONTRA NAVE
            if (s != NULL) {
                float d = (*ast) + s;

                if (d < ast->getSize() + s->getSize()) {
                    return 1;
                }
            }

            // ASTEROIDE CONTRA BALA
            if (b != NULL) {
                float d = (*ast) +b;

                if (d < ast->getSize() + b->getSize()) {
                    remove(b);

                    expl_pos[X] = ast->getX();
                    expl_pos[Y] = ast->getY();

                    if (ast->getAsteroidSize() == SMALL) {
                        remove(ast);
                        return 4;
                    }
                    else {
                        Asteroid* nuevo = ast->split();
                        add(nuevo);

                        if (ast->getAsteroidSize() == MEDIUM) {
                            return 3;
                        }
                        else {
                            return 2;
                        }
                    }
                }
            }
        }

        aux = aux->next;
    }

    return 0;
}

void ObjectsList::reposition(Ship* s) {
    nodo* aux = head;

    while (aux != NULL) {
        Asteroid* ast = dynamic_cast<Asteroid*>(aux->obj);

        if (ast != NULL && s != NULL) {
            float d = (*ast) + s;

            if (d < ast->getSize() + s->getSize() + 3) {
                ast->reposition();
            }
        }

        aux = aux->next;
    }
}