#include <iostream>
using std::cout;
using std::endl;
#include <fstream>
using std::ifstream;

#include <stdlib.h>
#include <stdio.h>

#include "Vect3.h"
#include "Color.h"
#include "Eye.h"
#include "Ray.h"
#include "LightSource.h"
#include "Light.h"
#include "Object.h"
#include "Sphere.h"

using namespace std;

struct SinglePixel {
	double r;
	double g;
	double b;
};

//creates file in ppm format
void save_ppm(int width, int height, char* fname, SinglePixel *pixel) {
  FILE *fp;
  const int maxVal=255; 
  int w = width;
  int h = height;
  int k = width*height;

  printf("Saving image %s: %d x %d\n", fname,width,height);
  fp = fopen(fname,"wb");
  if (!fp) {
        printf("Unable to open file '%s'\n",fname);
        return;
  }
  fprintf(fp, "P6\n");
  fprintf(fp, "%d %d\n", width, height);
  fprintf(fp, "%d\n", maxVal);

    fclose(fp);
}
//------------------------------------------------------------------------------

//Constant Declarations
const int MAX_CHARS_PER_LINE = 512;
const int MAX_TOKENS_PER_LINE = 20;
const int MAX_SPHERES = 14;
const int MAX_LIGHTS = 9;
const char* const DELIMITER = " ";
const char* const DELIMITER2 = "\t";
//Variable Declarations
int line_cnt = 0;
int token_cnt = 0;
int sphere_cnt = 0;
int light_cnt = 0;

int near,left,right,bottom,top;
//resolution
int nRows, nColumns;
//background
double bgRed, bgGreen, bgBlue;
//ambient color
double ambRed, ambGreen, ambBlue;
Color ambientColor = Color();
char outputFile[50];

//Spheres
//std::vector<Sphere> v;
string *sphere_name = new string[MAX_SPHERES];
char sph_name[MAX_SPHERES][20];
int sph_posX[MAX_SPHERES], sph_posY[MAX_SPHERES], sph_posZ[MAX_SPHERES];
double sph_sclX[MAX_SPHERES], sph_sclY[MAX_SPHERES], sph_sclZ[MAX_SPHERES];
double sph_red[MAX_SPHERES], sph_green[MAX_SPHERES], sph_blue[MAX_SPHERES];
double sph_K_amb[MAX_SPHERES], sph_K_diff[MAX_SPHERES], sph_K_spec[MAX_SPHERES], sph_K_refl[MAX_SPHERES], sph_n[MAX_SPHERES];

//Lights
char lt_name[9][20];
int lt_posX[9], lt_posY[9], lt_posZ[9];
double lt_red[9], lt_green[9], lt_blue[9];
int curr_pixel; //index value that changes -- to determine x and y coords of individual pixel


int main (int argc, char *argv[])
{

//save_ppm(width, height, outputFile, pixelppm); //output to ppm

//-------------START PARSER
  // create a file-reading object
  ifstream fin;
  fin.open(argv[1]); // open a file
  if (!fin.good()) 
    return 1; // exit if file not found

	return 0;
}