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
  
  // read each line of the file
  while (!fin.eof())
  {
    // read an entire line into memory
    char buf[MAX_CHARS_PER_LINE];
    fin.getline(buf, MAX_CHARS_PER_LINE);
    
    // parse the line into blank-delimited tokens
    int n = 0; // a for-loop index
    
    // array to store memory addresses of the tokens in buf
    const char* token[MAX_TOKENS_PER_LINE] = {}; // initialize to 0
    
    // parse the line
    token[0] = strtok(buf, DELIMITER); // first token
    if (token[0]) // zero if line is blank
    {
      for (n = 1; n < MAX_TOKENS_PER_LINE; n++)
      {
        token[n] = strtok(0, DELIMITER); // subsequent tokens
        token_cnt = n;
        if (!token[n]) break; // no more tokens
      }
    }

//-------------------------------------------------------
//check and validate file
//NEAR
if ((!strcmp(token[0],"NEAR")) && (token_cnt == 2)) 
{
	printf("Correct!! line#: %d, tokens#: %d \n", line_cnt, token_cnt);
}
//LEFT
else if ((!strcmp(token[0],"LEFT")) && (token_cnt == 2)) 
{
	printf("Correct!! line#: %d, tokens#: %d \n", line_cnt, token_cnt);
}
//RIGHT
else if ((!strcmp(token[0],"RIGHT")) && (token_cnt == 2)) 
{
	printf("Correct!! line#: %d, tokens#: %d \n", line_cnt, token_cnt);
}
//BOTTOM
else if ((!strcmp(token[0],"BOTTOM")) && (token_cnt == 2)) 
{
	printf("Correct!! line#: %d, tokens#: %d \n", line_cnt, token_cnt);
}
//TOP
else if ((!strcmp(token[0],"TOP")) && (token_cnt == 2)) 
{
	printf("Correct!! line#: %d, tokens#: %d \n", line_cnt, token_cnt);
}
//RESOLUTION
else if ((!strcmp(token[0],"RES")) && (token_cnt == 3)) 
{
	nRows = atoi(token[1]);
	nColumns = atoi(token[2]);

	printf("Correct!! line#: %d, tokens#: %d \n", line_cnt, token_cnt);
}

//########## fix from here down to count how many spheres
//SPHERE --> up to 14
else if ((!strcmp(token[0],"SPHERE")) && (token_cnt == 16)) 
{
	printf("Correct!! line#: %d, tokens#: %d \n", line_cnt, token_cnt);
	
	if ((!strcmp(token[0],"SPHERE")))
	{
		sphere_cnt++;
		printf("IS A SPHERE --- %d\n",sphere_cnt);

		//<name>
		strncpy(sph_name[sphere_cnt],token[1],20);
		printf("%s\n",sph_name[sphere_cnt]);

		//<pos>
		sph_posX[sphere_cnt] = atoi(token[2]);
		sph_posY[sphere_cnt] = atoi(token[3]);
		sph_posZ[sphere_cnt] = atoi(token[4]);
		//<scale>
		sph_sclX[sphere_cnt] = strtod(token[5],NULL);
		sph_sclY[sphere_cnt] = strtod(token[6],NULL);
		sph_sclZ[sphere_cnt] = strtod(token[7],NULL);
		//<color>
		sph_red[sphere_cnt] = strtod(token[8],NULL);
		sph_green[sphere_cnt] = strtod(token[9],NULL);
		sph_blue[sphere_cnt] = strtod(token[10],NULL);

		//<k-values>
		sph_K_amb[sphere_cnt] = strtod(token[11],NULL);
		sph_K_diff[sphere_cnt] = strtod(token[12],NULL);
		sph_K_spec[sphere_cnt] = strtod(token[13],NULL);
		sph_K_refl[sphere_cnt] = strtod(token[14],NULL);

		//<n-value>
		sph_n[sphere_cnt] = strtod(token[15],NULL);
	}
}
//########### fix from here down to count how many lights
//LIGHT --> up to 9
else if ((!strcmp(token[0],"LIGHT")) && (token_cnt == 8)) 
{
	printf("Correct!! line#: %d, tokens#: %d \n", line_cnt, token_cnt);
	if ((!strcmp(token[0],"LIGHT")))
	{
		light_cnt++;
		printf("IS A LIGHT --- %d\n",light_cnt);

		//<name>
		strncpy(lt_name[light_cnt],token[1],20);
		printf("%s\n",lt_name[light_cnt]);

		//<pos>
		lt_posX[light_cnt] = atoi(token[2]);
		lt_posY[light_cnt] = atoi(token[3]);
		lt_posZ[light_cnt] = atoi(token[4]);

		//<color>
		lt_red[light_cnt] = strtod(token[5],NULL);
		lt_green[light_cnt] = strtod(token[6],NULL);
		lt_blue[light_cnt] = strtod(token[7],NULL);
	}
}

//BACKGROUND
else if ((!strcmp(token[0],"BACK")) && (token_cnt == 4)) 
{
	printf("Correct!! line#: %d, tokens#: %d \n", line_cnt, token_cnt);
	bgRed = strtod(token[1],NULL);
	bgGreen = strtod(token[2],NULL);
	bgBlue = strtod(token[3],NULL);

}

//AMBIENT
else if ((!strcmp(token[0],"AMBIENT")) && (token_cnt == 4)) 
{
	printf("Correct!! line#: %d, tokens#: %d \n", line_cnt, token_cnt);
	ambRed = strtod(token[1],NULL);
	ambGreen = strtod(token[2],NULL);
	ambBlue = strtod(token[3],NULL);
	ambientColor.setRed(ambRed);
	ambientColor.setGreen(ambGreen);
	ambientColor.setBlue(ambBlue);


}

//FILE OUTPUT
else if ((!strcmp(token[0],"OUTPUT")) && (token_cnt == 2)) 
{
	printf("Correct!! line#: %d, tokens#: %d \n", line_cnt, token_cnt);
strncpy(outputFile,token[1],20);
}

else if ((!strcmp(token[0]," ")) || (!strcmp(token[0],"\t")))
{
printf("BLANK\n");
}
//-------------------------------------------------------

    // process (print) the tokens
    for (int i = 0; i < n; i++) // n = #of tokens
      cout << "Token[" << i << "] = " << token[i] << endl;
    cout << endl;

    line_cnt++;
  }










//--------------END PARSER

	return 0;
}