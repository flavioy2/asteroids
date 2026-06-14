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

void ObjectsList::add(Shape *shape) {
  Nodo *nuevo = new Nodo();
  nuevo->obj = shape;
  nuevo->next = head;
  head = nuevo;
  n++;
}

void ObjectsList::remove(Shape *shape) {
  if (shape == NULL)
    return;

  Nodo *actual = head;
  Nodo *anterior = NULL;

  while (actual != NULL) {
    if (actual->obj == shape) {
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
  if (tiempoOVNI > 1500 && theOvni == NULL) { // APARECE UN OVNI PERIODICAMENTE
    theOvni = new Ovni(1);
    add(theOvni);
    tiempoOVNI = 0;
  }

  Nodo *actual = head;
  while (actual != NULL) {
    actual->obj->move();
    actual = actual->next;
  }
}

void ObjectsList::draw() {
  Nodo *actual = head;
  while (actual != NULL) {
    actual->obj->draw();
    actual = actual->next;
  }
}

Ship *ObjectsList::getShip() { return theShippa; }

void ObjectsList::reposition(Ship *ship) {
  Nodo *actual = head;
  while (actual != NULL) {
    Asteroid *asteroid = dynamic_cast<Asteroid *>(actual->obj); // COMPROBAMOS SI EL OBJETO ES UN ASTEROIDE
    if (asteroid != NULL) {
      float apos[3];
      asteroid->getPos(apos);
      if (mydistance(apos[X], apos[Y], 0, 0) < 2 * asteroid->getSize()) // SI EL ASTEROIDE ESTA CERCA DEL CENTRO DE LA PANTALLA SE REPOSICIONA
        asteroid->reposition();
    }
    actual = actual->next;
  }
  theShippa = ship;
  add(theShippa); // INSERTAMOS LA NAVE
}

int ObjectsList::collisions(Bullet *bullet, Ship *ship, float *expl_pos) {
  Nodo *actual = head;
  while (actual != NULL) {
    Asteroid *asteroid = dynamic_cast<Asteroid *>(actual->obj); // COMPROBAMOS SI EL OBJETO ES UN ASTEROIDE
    if (asteroid != NULL) {
      if (ship != NULL) {
        float spos[3];
        ship->getPos(spos);
        if ((*asteroid + ship) < asteroid->getSize() + ship->getSize()) { // COLISION ENTRE ASTEROIDE Y NAVE
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
        if ((*asteroid + bullet) < asteroid->getSize() + bullet->getSize()) { // COLISION ENTRE ASTEROIDE Y BALA
          expl_pos[X] = apos[X];
          expl_pos[Y] = apos[Y];
          remove(bullet);
          if (asteroid->getSize() == SMALL * 0.3f) {
            remove(asteroid);
            return 4;
          } else {
            Asteroid *nuevo = asteroid->split();
            add(nuevo);
            if (asteroid->getSize() == MEDIUM * 0.3f)
              return 2;
            else
              return 3;
          }
        }
      }
    }
    Ovni *ovni = dynamic_cast<Ovni *>(actual->obj); // IGUAL QUE ANTES, COMPROBAMOS SI EL OBJETO ES UN OVNI
    if (ovni != NULL && bullet != NULL) {
      if ((*ovni + bullet) < ovni->getSize() + bullet->getSize()) { // COLISION ENTRE OVNI Y BALA
        remove(bullet);
        remove(ovni);
        theOvni = NULL;
        tiempoOVNI = 0; 
        if (ovni->getSize() == BIG * 0.3)
          return 5;
        if (ovni->getSize() == MEDIUM * 0.3)
          return 6;
        return 7;
      }
    }
    actual = actual->next;
  }
  return 0;
}

// DESTRUIMOS LA LISTA Y LIBERAMOS LA MEMORIA
ObjectsList::~ObjectsList() {
  Nodo *actual = head;
  while (actual != NULL) {
    Nodo *siguiente = actual->next;
    delete actual->obj;
    delete actual;
    actual = siguiente;
  }
}
