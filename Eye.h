#ifndef _EYE_H
#define _EYE_H

#include "Vect3.h"


class Eye {
	Vect3 eyepos, eyedir, eyeright, eyedown;
	
	public:
	
	Eye ();
	
	Eye (Vect3, Vect3, Vect3, Vect3);
	
	// method functions
	Vect3 getEyePosition () { return eyepos; }
	Vect3 getEyeDirection () { return eyedir; }
	Vect3 getEyeRight () { return eyeright; }
	Vect3 getEyeDown () { return eyedown; }
	
};

//default constructor
Eye::Eye () {
	eyepos = Vect3(0,0,0);
	eyedir = Vect3(0,0,1);
	eyeright = Vect3(0,0,0);
	eyedown = Vect3(0,0,0);
}

//specified constructor
Eye::Eye (Vect3 pos, Vect3 dir, Vect3 right, Vect3 down) {
	eyepos = pos;
	eyedir = dir;
	eyeright = right;
	eyedown = down;
}

#endif