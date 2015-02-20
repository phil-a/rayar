#ifndef _LIGHT_H
#define _LIGHT_H

#include "Vect3.h"
#include "Color.h"
#include "LightSource.h"
// light similar to ray, but have colors


class Light : public LightSource {
	Vect3 position;
	Color color;

public:
	Light();
//constructor
	Light (Vect3, Color);
	
//methods
	virtual Vect3 getLightPosition () { return position; }
	virtual Color getLightColor () { return color; }
};

//default constructor
Light::Light () {
	position = Vect3(0,0,0);
	color = Color(1,1,1, 0);
}

//specified constructor
Light::Light (Vect3 p, Color c) {
	position = p;
	color = c;
}

#endif