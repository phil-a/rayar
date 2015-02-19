#ifndef _RAY_H
#define _RAY_H

#include "Vect3.h"


class Ray
{
	Vect3 origin, direction; //each ray has origin and direction
	
public:
	Ray();
//constructor
	Ray (Vect3, Vect3);
	
//methods
	Vect3 getRayOrigin () { return origin; }
	Vect3 getRayDirection () { return direction; }
};

//default constructor
Ray::Ray () {
	origin = Vect3(0,0,0);
	direction = Vect3(1,0,0);
}

//specified constructor
Ray::Ray (Vect3 o, Vect3 d) {
	origin = o;
	direction = d;
}

#endif