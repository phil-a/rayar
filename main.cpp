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

//Variable Declarations
int line_cnt = 0;
int token_cnt = 0;

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