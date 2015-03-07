#ifndef _Plane_H
#define _Plane_H

#include "math.h"
#include "Object.h"
#include "Vect3.h"
#include "Color.h"

class Plane : public Object {
	double distance;
	Vect3 normal;
	Color color;
	
	public:
	
	Plane ();
	
	Plane (double, Vect3, Color);
	
	// method functions
	double getDistance () { return distance; }
	Vect3 getNormal () { return normal; }
	virtual Color getColor () { return color; }
	
	virtual Vect3 getNormalAtPoint(Vect point) {
		return normal;
	}
	
	virtual double getIntersection(Ray ray) {
		Vect3 ray_direction = ray.getRayDirection();
		
		double a = ray_direction.dotProd(normal);
		if (a == 0) {
			return -1;
		}
		//ray not parallel to plane
		else {
			double b = normal.dotProd(ray.getRayOrigin().vect3Add(normal.vect3Mult(distance).negative()));
			return -1*b/a;
		}
	}
	
};

Plane::Plane () {
	normal = Vect3(1,0,0);
	distance = 0;
	color = Color(0.5,0.5,0.5, 0);
}

Plane::Plane (double dv, Vect nv, Color cv) {
	distance = dv;
	normal = nv;
	color = cv;
}

#endif
