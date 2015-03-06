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

//Clip color to not exceed certain values
	Color clip()
	{
		double all_light = red + green + blue;
		double excess_light = all_light - 3;
		if (excess_light > 0)
		{
			red = red + excess_light*(red/all_light);
			green = green + excess_light*(green/all_light);
			blue = blue + excess_light*(blue/all_light);

		}
		if (red > 1) {red = 1;}
		if (green> 1) {green = 1;}
		if (blue > 1) {blue = 1;}

		if (red < 0) {red = 0;}
		if (green<  0) {green = 0;}
		if (blue < 0) {blue = 0;}

		return Color (red, green, blue, alpha);

	}
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