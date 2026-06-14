
#include "Asteroid.h"
#include "Bullet.h"
#include "Ovni.h"
#include "Shape.h"
#include "Ship.h"
#include "commonstuff.h"

#ifndef __OL_H__
#define __OL_H__

struct Nodo {
  Shape *obj;
  Nodo *next;
};

class ObjectsList {
private:
  int n;
  Nodo *head;
  Ship *theShippa;
  Ovni *theOvni;
  int tiempoOVNI;

public:
  ObjectsList();
  ~ObjectsList();
  void move();
  void draw();
  void add(Shape *);
  // ObjectsList* getNext();
  void remove(Shape *);
  Ship *getShip();
  int collisions(Bullet *, Ship *, float *expl_pos);
  void reposition(Ship *);
};

#endif
