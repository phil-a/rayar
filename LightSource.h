#ifndef _LIGHTSOURCE_H
#define _LIGHTSOURCE_H

#include "Ray.h"
#include "Vect3.h"
#include "Color.h"


class LightSource
{

public:
	LightSource();
//constructor
	
//methods
	virtual Vect3 getLightPosition () { return Vect3 (0.0, 0.0, 0.0); }
	virtual Color getColor () { return Color (1, 1, 1, 0); }
	
};

//default constructor
LightSource::LightSource ()
{

}


#endif