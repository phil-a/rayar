#ifndef _COLOR_H
#define _COLOR_H


class Color
{
	double red, green, blue, alpha;

public:
	//constructors
	Color();
	Color(double,double,double, double);
	
//methods
	double getRed() { return red; }
	double getGreen() { return green; }
	double getBlue() { return blue; }
	double getAlpha() { return alpha; }
	
	double setRed(double redValue) { red = redValue; return red; }
	double setGreen(double greenValue) { green = greenValue; return green; }
	double setBlue(double blueValue) { blue = blueValue; return blue;}
	double setAlpha(double alphaValue) { alpha = alphaValue; return alpha; }

	//for shadows
	double brightness()
	{
		return(red + green + blue)/3;
	}

//scales color by a factor
	Color colorScalar (double scalar){
		return Color (red*scalar, green*scalar, blue*scalar, alpha);
	}

//addition blend of two colors
	Color colorAdd(Color otherColour)
	{
		return Color (red + otherColour.getRed(),green + otherColour.getGreen(),blue + otherColour.getBlue(), alpha);
	}

	Color colorMultiply(Color otherColour)
	{
		return Color(red*otherColour.getRed(), green*otherColour.getGreen(), blue*otherColour.getBlue(), alpha);
	}

//average of colors
	Color colorAverage (Color color)
	{
		return Color ((red + color.getRed()/2),(green + color.getGreen()/2), (blue + color.getBlue()/2), alpha);
	}

//
};


//default Color constructor

Color::Color () {
	red = 0.5;
	green = 0.5;
	blue = 0.5;
}

//specified Colortor constructor
Color::Color (double r, double g, double b, double a) {
	red = r;
	green = g;
	blue = b;
	alpha = a;
}

#endif