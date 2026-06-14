
#include "commonstuff.h"
#include "Shape.h"
#include "Asteroid.h"
#include "Ship.h"
#include "Bullet.h"
#include "OVNI.h"

#ifndef __OL_H__
#define __OL_H__

typedef 
struct nodo {
	Shape* obj;
	struct nodo* next;
} nodo;

class ObjectsList{
 private:
  int n;
   nodo *head;
  Ship *theShippa;
  OVNI* theOvni;
  int tiempoOVNI;
  
 public:
  ObjectsList();
  ~ObjectsList();
  void move();
  void draw();
  void add(Shape*);
  // ObjectsList* getNext();
  void remove(Shape*);
  Ship* getShip();
  int collisions(Bullet*,Ship*,float *expl_pos);
  void reposition(Ship *);
};

#endif
