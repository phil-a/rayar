#ifndef _VECT3_H
#define _VECT3_H

#include "math.h"

class Vect3
{
	double x, y, z;

public:
	//constructors
	Vect3();
	Vect3(double,double,double);
	
//methods
	double getVectX() {return x;}
	double getVectY() {return y;}
	double getVectZ() {return z;}

	double magnitude ()
	{
		return sqrt((x*x) + (y*y) + (z*z));
	}

	Vect3 normalize ()
	{
				double magnitude = sqrt((x*x) + (y*y) + (z*z));
		return Vect3 (x/magnitude, y/magnitude, z/magnitude);
	}

	Vect3 negative ()
	{
		return Vect3 (-x, -y, -z);
	}

	double dotProd(Vect3 v)
	{
		return x*v.getVectX() + y*v.getVectY() + z*v.getVectZ();
	}

	Vect3 crossProd(Vect3 v)
	{
		return Vect3 (y*v.getVectZ() - z*v.getVectY(), z*v.getVectX() - x*v.getVectZ(), x*v.getVectY() - y*v.getVectX());
	}

	Vect3 vect3Add (Vect3 v) {
		return Vect3 (x + v.getVectX(), y + v.getVectY(), z + v.getVectZ());
	}

	Vect3 vect3Mult (double scalar) {
		return Vect3 (x*scalar, y*scalar, z*scalar);
	}

	Vect3 operator+(Vect3 v) {
		return Vect3 (x + v.getVectX(), y + v.getVectY(), z + v.getVectZ());
	}
	
	Vect3 operator*(double other)
	const
	{
		return Vect3 (x*other, y*other, z*other);
	}


};


//default Vector constructor
Vect3::Vect3 () {
	x = 0;
	y = 0;
	z = 0;
}

//specified Vector constructor
Vect3::Vect3 (double i, double j, double k) {
	x = i;
	y = j;
	z = k;
}

#endif