#include <iostream>
using std::cout;
using std::endl;
#include <fstream>
using std::ifstream;

#include <stdlib.h>
#include <stdio.h>

#include "Vect3.h"

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


int main (int argc, char *argv[])
{

//save_ppm(width, height, outputFile, pixelppm); //output to ppm

	return 0;
}