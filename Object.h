#ifndef _OBJECT_H
#define _OBJECT_H

#include "Ray.h"
#include "Vect3.h"
#include "Color.h"


class Object
{

public:
	Object();
//constructor
	
//methods
	virtual Color getColor () { return Color (0.0, 0.0, 0.0, 0); }
	
	virtual Vect3 getNormalAt(Vect3 intersection_position) {
		return Vect3 (0, 0, 0);
	}
	
	virtual double findIntersection(Ray ray) {
		return 0;
	}
	
};

//default constructor
Object::Object ()
{

}


#endif