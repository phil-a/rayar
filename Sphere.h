#ifndef _SPHERE_H
#define _SPHERE_H

#include "math.h"
#include "Object.h"
#include "Vect3.h"
#include "Color.h"
	
const double PREC_OFFSET = 0.000001;

class Sphere : public Object
{
	Vect3 center;
	double radius;
	Color color;
	double amb;
	double diff;
	double spec;
	double refl;

public:
	Sphere();
//constructor
	Sphere (Vect3, double, Color, double, double, double, double);
	
//methods
	Vect3 getSphereCenter () { return center; }
	double getSphereRadius () { return radius; }
	virtual Color getColor () { return color; }
	double getAmb () { return amb; }
	double getDiff () { return diff; }
	double getSpec () { return spec; }
	double getRefl () { return refl; }

	virtual Vect3 getNormalAt(Vect3 point) {
		//normal points away from center of sphere
		Vect3 normal_Vect = point.vect3Add(center.negative()).normalize();
		return normal_Vect;
	}
	virtual double findIntersection(Ray ray) {
		Vect3 ray_origin = ray.getRayOrigin();
		double ray_origin_x = ray_origin.getVectX();
		double ray_origin_y = ray_origin.getVectY();
		double ray_origin_z = ray_origin.getVectZ();
		
		Vect3 ray_direction = ray.getRayDirection();
		double ray_direction_x = ray_direction.getVectX();
		double ray_direction_y = ray_direction.getVectY();
		double ray_direction_z = ray_direction.getVectZ();
		
		Vect3 sphere_center = center;
		double sphere_center_x = sphere_center.getVectX();
		double sphere_center_y = sphere_center.getVectY();
		double sphere_center_z = sphere_center.getVectZ();
		
		double a = 1; // normalized
		double b = (2*(ray_origin_x - sphere_center_x)*ray_direction_x) + (2*(ray_origin_y - sphere_center_y)*ray_direction_y) + (2*(ray_origin_z - sphere_center_z)*ray_direction_z);
		double c = pow(ray_origin_x - sphere_center_x, 2) + pow(ray_origin_y - sphere_center_y, 2) + pow(ray_origin_z - sphere_center_z, 2) - (radius*radius);
		
		double discriminant = b*b - 4*c;

		if (discriminant > 0) //ray intersects sphere
		{
			//first root
			double root_1 = ((-1*b - sqrt(discriminant))/2) - PREC_OFFSET;
			if (root_1 > 0)
			//this root is smallest positive root
			{
				return root_1;
			}
			else //this root2  smallest positive root
			{
				double root_2 = ((sqrt(discriminant) - b)/2) - PREC_OFFSET;
				return root_2;
			}
		}
		else //ray did not hit sphere at all
		{
			return -1;
		}
	}
};

//default constructor
Sphere::Sphere () {
	center = Vect3(0,0,0);
	radius = 1.0;
	color = Color(0.5,0.5,0.5, 0);
	amb = 1;
	diff = 1;
	spec = 1;
	refl = 1;
}

//specified constructor
Sphere::Sphere (Vect3 centerNew, double radiusNew, Color colorNew, double ambNew, double diffNew, double specNew, double reflNew) {
	center = centerNew;
	radius = radiusNew;
	color = colorNew;
	amb = ambNew;
	diff = diffNew;
	spec = specNew;
	refl = reflNew;
}

#endif